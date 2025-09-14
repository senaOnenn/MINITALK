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

void	send_signal(int server_pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> (7 - i)) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		i++;
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	server_pid;

	i = 0;
	server_pid = ft_atoi(argv[1]);
	if (argc != 3)
	{
		write(1, "Usage: ./client <PID> <message>\n", 33);
		return (1);
	}
	while (argv[2][i])
	{
		send_signal(server_pid, argv[2][i]);
		i++;
	}
	send_signal(server_pid, '\0');
}
