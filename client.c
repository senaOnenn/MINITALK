/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:07:08 by eonen             #+#    #+#             */
/*   Updated: 2025/09/22 18:31:32 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_flag = 0;

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_flag = 1;
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_ack_flag = 0;
		if ((c >> (7 - i)) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_ack_flag)
			pause();
		i++;
	}
}

void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	sigact;

	if (argc != 3)
	{
		write(1, "Usage: ./client <PID> <message>\n", 33);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || pid > 4194304 || ft_strlen(argv[1]) > 8)
		write(1, "Error: Invalid PID!\n", 21);
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = ack_handler;
	sigact.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
	{
		write(1, "Error: sigaction failed\n", 24);
		exit(1);
	}
	i = 0;
	send_message(pid, argv[2]);
	send_char(pid, '\0');
	return (0);
}
