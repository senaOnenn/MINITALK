/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:30:01 by eonen             #+#    #+#             */
/*   Updated: 2025/09/21 17:25:08 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_ack_received = 0;
		if ((c >> (7 - i)) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);

		while (!g_ack_received)
			pause();
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
	{
		write(1, "Usage: ./client <PID> <message>\n", 33);
		return (1);
	}

	pid = ft_atoi(argv[1]);
	if (pid <= 0 || pid > 4194304 || ft_strlen(argv[1]) > 8)
		write(1,"Error: Invalid PID!\n",21);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		write(1, "Error: sigaction failed\n", 24);

	i = 0;
	while (argv[2][i])
	{
		send_char(pid, argv[2][i]);
		i++;
	}
	send_char(pid, '\0');

	return (0);
}
