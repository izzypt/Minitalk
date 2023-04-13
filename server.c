/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:57:33 by smagalha          #+#    #+#             */
/*   Updated: 2023/04/08 22:45:36 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_signal(int sig, siginfo_t *info, void *context);

int	main(void)
{
	struct sigaction	action;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	action.sa_sigaction = handle_signal;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
	while (1)
		pause();
	return (0);
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_count;
	static unsigned char	c;

	(void)context;
	c |= (sig == SIGUSR2);
	if (++bit_count == 8)
	{
		bit_count = 0;
		if (!c)
		{
			kill(info->si_pid, SIGUSR2);
			info->si_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
	}
	else
		c <<= 1;
}
