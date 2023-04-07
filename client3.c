/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:55:33 by smagalha          #+#    #+#             */
/*   Updated: 2023/04/07 23:55:34 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int	ft_atoi(const char *s)
{
	size_t		i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return ((int)(res * sign));
}

void	send_bit(int bit, int pid)
{
	if (bit == 0)
	{
		// Send SIGUSR1 signal for bit 0
		kill(pid, SIGUSR1);
	}
	else if (bit == 1)
	{
		// Send SIGUSR2 signal for bit 1
		kill(pid, SIGUSR2);
	}
}

void	send_char(char c, int pid)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		// Get the i-th bit of the character
		int		bit;

		bit = (c >> i) & 1;
		send_bit(bit, pid);
		// Sleep for 1 millisecond to avoid flooding the signal queue
		usleep(1000);
		i++;
	}
}

void	send_string(char *str, int pid)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < strlen(str))
	{
		send_char(str[i], pid);
		i++;
	}
	// Signal end of transmission with 8 SIGUSR1 signals
	while (j < 8)
	{
		send_bit(0, pid);
		usleep(1000);
		j++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Please provide a pid and a signal...");
		return (1);
	}
	//printf("The process id of the server is: %d\n", 526);
	printf("Client ready to send signals..\n");
	printf("%d %d\n", ft_atoi(argv[1]), ft_atoi(argv[2]));
	//kill(ft_atoi(argv[1]), ft_atoi(argv[2]));
	send_string("Simao", ft_atoi(argv[1]));
	return (1);
}
