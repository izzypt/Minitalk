/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:46:42 by smagalha          #+#    #+#             */
/*   Updated: 2023/04/08 00:03:18 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void	signal_handler(int sig)
{
	static char		received_char;
	static int		bit_count;

	received_char = 0;
	bit_count - 0;
	if (sig == SIGUSR1)
	{
		// Received a 0 bit
		received_char |= (0 << bit_count);
	}
	else if (sig == SIGUSR2)
	{
		// Received a 1 bit
		received_char |= (1 << bit_count);
	}
	bit_count++;
	if (bit_count == 8) 
	{
		// Received a full character, print it to stdout
		putchar(received_char);
		fflush(stdout);
		bit_count = 0;
		received_char = 0;
	}
}

int	main(int argc, char **argv)
{
	// Set up signal handler for SIGUSR1 and SIGUSR2
	printf("teste");
	printf("Process id: %d", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
