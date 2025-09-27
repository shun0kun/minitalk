#include "client.h"

static char	g_ack;
static char	g_server_pid;

void	receive_acknowledge(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (info->si_pid == g_server_pid)
		g_ack = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					i;
	int					j;
	int					bit;

	if (argc != 3)
		return (-1);
	ft_memset(sa, 0, sizeof(sa));
	sa.sa_sigaction = receive_acknowledge;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	g_server_pid = ft_atoi(argv[1]);
	i = 0;
	while (i < sizeof(argv[2]))
	{
		j = 0;
		while (j < 8)
		{
			bit = (argv[2][i] >> j) & 1;
			if (bit == 0)
			{
				kill(ft_atoi(argv[1]), SIGUSR1);
			}
			else
			{
				kill(ft_atoi(argv[1]), SIGUSR2);
			}
			j++;
			while (!g_ack)
			{
				usleep(50);
			}
			g_ack = 0;
		}
		i++;
	}
	return (0);
}
