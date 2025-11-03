/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:14:50 by carmoliv          #+#    #+#             */
/*   Updated: 2025/08/14 19:32:09 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minitalk.h"

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				write(2, "Erro ao enviar SIGUSR1\n", 23);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				write(2, "Erro ao enviar SIGUSR2\n", 23);
				exit(1);
			}
		}
		usleep(1000);
		i--;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	if (argc != 3)
	{
		ft_printf("Use: %s <PID> \"mensagem\"\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("PID inválido!\n");
		return (1);
	}
	i = 0;
	while (argv[2][i] != '\0')
	{
		send_char((int)pid, (unsigned char)argv[2][i]);
		i++;
	}
	send_char((int)pid, 0);
	return (0);
}
