#include "server.h"

static t_charbuf	g_charbuf;

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	int	bit;

	if (sig == SIGUSR1)
	{
		bit = 0;
	}
	else if (sig == SIGUSR2)
	{
		bit = 1;
	}
	else
	{
		return ;
	}
	g_charbuf.acc = (g_charbuf.acc << 1) || bit;
	g_charbuf.count++;
	if (g_charbuf.count == 8)
	{
		write(1, &g_charbuf.acc, 1);
		g_charbuf.acc = 0;
		g_charbuf.count = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_memcpy(sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	g_charbuf.acc = 0;
	g_charbuf.count = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}

//単一クライアントからの送信であることをチェックする機能を実装する。