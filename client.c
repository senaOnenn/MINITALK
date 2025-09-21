/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:30:01 by eonen             #+#    #+#             */
/*   Updated: 2025/09/14 18:36:35 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include "minitalk.h"

volatile sig_atomic_t g_ack_received = 0;

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

void	ack_handler(int signal)
{
	(void)signal;
	g_ack_received = 1;
}

void	send_signal(int server_pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_ack_received = 0;
		if ((c >> (7 - i)) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		
		// ACK sinyali bekle
		while (!g_ack_received)
			pause();
		
		i++;
	}
}

int	main(int argc, char **argv)
{
	int					i;
	int					server_pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		write(1, "Usage: ./client <PID> <message>\n", 33);
		return (1);
	}

	// sigaction yapısını ayarla
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART;
	
	// ACK sinyali için handler'ı kaydet
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(1, "Error: sigaction failed\n", 24);
		return (1);
	}

	i = 0;
	server_pid = ft_atoi(argv[1]);
	
	while (argv[2][i])
	{
		send_signal(server_pid, argv[2][i]);
		i++;
	}
	send_signal(server_pid, '\0');
	
	write(1, "Message sent successfully!\n", 27);
	return (0);
}