/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:15:14 by carmoliv          #+#    #+#             */
/*   Updated: 2025/08/14 18:17:16 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	put_pid(int pid)
{
	int		i;
	char	buf[12];

	i = 10;
	buf[11] = '\0';
	if (pid == 0)
	{
		write(1, "0", 1);
		return ;
	}
	while (pid > 0 && i >= 0)
	{
		buf[i--] = (pid % 10) + '0';
		pid /= 10;
	}
	write(1, &buf[i + 1], 10 - i);
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	static t_data	data = {0, 0, 0};

	(void)context;
	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	if (data.last_pid != info->si_pid && data.bits == 0)
	{
		write(1, "\nMensagem cliente PID: ", 24);
		put_pid(info->si_pid);
		write(1, "\n", 1);
		data.last_pid = info->si_pid;
	}
	data.c <<= 1;
	if (sig == SIGUSR1)
		data.c |= 1;
	data.bits++;
	if (data.bits == 8)
	{
		if (data.c == 0)
			write(1, "\n", 1);
		else
			write(1, &data.c, 1);
		data.bits = 0;
		data.c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction SIGUSR1");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction SIGUSR2");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
