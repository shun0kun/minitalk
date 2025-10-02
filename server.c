/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimots <sshimots@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:08:11 by sshimots          #+#    #+#             */
/*   Updated: 2025/10/02 13:37:32 by sshimots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_recv	g_recv;

int	receive_bit(int sig)
{
	int	bit;

	if (sig == SIGUSR1)
		bit = 0;
	else if (sig == SIGUSR2)
		bit = 1;
	else
		return (0);
	g_recv.wd = 0;
	g_recv.acc = (unsigned char)((g_recv.acc << 1) | bit);
	if (g_recv.count < 8)
		g_recv.count++;
	return (1);
}

void	cleanup_g_recv(void)
{
	g_recv.acc = 0;
	g_recv.count = 0;
	g_recv.client_pid = 0;
	g_recv.wd = 0;
}

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (!info || (g_recv.client_pid && g_recv.client_pid != info->si_pid))
		return (cleanup_g_recv(), (void)0);
	else if (g_recv.client_pid == 0)
	{
		cleanup_g_recv();
		g_recv.client_pid = info->si_pid;
	}
	if (!receive_bit(sig))
		return (cleanup_g_recv(), (void)0);
	if (g_recv.count == 8)
	{
		if (g_recv.acc == '\0')
		{
			kill(info->si_pid, SIGUSR1);
			return (cleanup_g_recv(), (void)0);
		}
		write(1, &g_recv.acc, 1);
		g_recv.acc = 0;
		g_recv.count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	server_init(struct sigaction *p_sa)
{
	ft_memset(p_sa, 0, sizeof(*p_sa));
	p_sa->sa_flags = SA_SIGINFO;
	p_sa->sa_sigaction = handle_signal;
	sigemptyset(&p_sa->sa_mask);
	sigaddset(&p_sa->sa_mask, SIGUSR1);
	sigaddset(&p_sa->sa_mask, SIGUSR2);
	sigaction(SIGUSR1, p_sa, NULL);
	sigaction(SIGUSR2, p_sa, NULL);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID = %d\n", getpid());
	server_init(&sa);
	while (1)
	{
		usleep(1000);
		if (g_recv.client_pid)
		{
			g_recv.wd++;
			if (g_recv.wd > 5000)
			{
				ft_printf("Time out\n");
				cleanup_g_recv();
			}
		}
	}
}
