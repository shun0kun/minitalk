/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimots <sshimots@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:05:36 by sshimots          #+#    #+#             */
/*   Updated: 2025/10/02 13:20:29 by sshimots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define _POSIX_C_SOURCE	200809L
# define _DEFAULT_SOURCE  

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_ack
{
	volatile sig_atomic_t	ack_received;
	pid_t					server_pid;
}	t_ack;

#endif