/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimots <sshimots@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:29:04 by sshimots          #+#    #+#             */
/*   Updated: 2025/10/02 13:20:28 by sshimots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_ack	g_ack;

void	receive_ack(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGUSR1 && info && info->si_pid == g_ack.server_pid)
		g_ack.ack_received = 1;
}

void	client_init(struct sigaction *p_sa, char **argv)
{
	ft_memset(p_sa, 0, sizeof(*p_sa));
	p_sa->sa_flags = SA_SIGINFO;
	p_sa->sa_sigaction = receive_ack;
	sigemptyset(&p_sa->sa_mask);
	sigaddset(&p_sa->sa_mask, SIGUSR1);
	sigaction(SIGUSR1, p_sa, NULL);
	g_ack.server_pid = (pid_t)ft_atoi(argv[1]);
}

void	send_bit(char c, int bit_index)
{
	int	bit;

	bit = ((unsigned char)c >> bit_index) & 1;
	if (bit == 0)
		kill(g_ack.server_pid, SIGUSR1);
	else
		kill(g_ack.server_pid, SIGUSR2);
}

void	wait_for_ack(void)
{
	int	count;

	count = 0;
	while (!g_ack.ack_received)
	{
		usleep(100);
		count++;
		if (count > 1000)
		{
			ft_printf("Time out\n");
			exit(1);
		}
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					i;
	int					bit_index;
	int					message_len;

	if (argc != 3)
		return (-1);
	client_init(&sa, argv);
	message_len = ft_strlen(argv[2]);
	i = 0;
	while (i <= message_len)
	{
		bit_index = 7;
		while (bit_index >= 0)
		{
			g_ack.ack_received = 0;
			send_bit(argv[2][i], bit_index);
			bit_index--;
			wait_for_ack();
		}
		i++;
	}
	return (0);
}
