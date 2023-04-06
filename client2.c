#include "minitalk.h"

static void	send_bits(int pid, char *str);
static void	handle_signal(int sig);

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 1);
		return (1);
	}
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	send_bits(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}

static void	send_bits(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

static void	handle_signal(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("Message was received by the server\n", 1);
		exit(0);
	}
}
