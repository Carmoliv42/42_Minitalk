/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:15:19 by carmoliv          #+#    #+#             */
/*   Updated: 2025/08/14 18:13:38 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
#  define _XOPEN_SOURCE 500
# endif

# include <unistd.h>
# include <time.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_data
{
	unsigned char	c;
	int				bits;
	pid_t			last_pid;
}	t_data;

#endif