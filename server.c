/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:30:05 by eonen             #+#    #+#             */
/*   Updated: 2025/09/14 18:36:37 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signal)
{
	static char	character;
	static int	current_bit;

	if (signal == SIGUSR2)
		character = character | 1;
	current_bit++;
	if (current_bit == 8)
	{
		write(1, &character, 1);
		character = 0;
		current_bit = 0;
	}
	else
	{
		character <<= 1;
	}
}

void	write_pid(int pid)
{
	char	pid_string[12];
	int		i;

	i = 11;
	pid_string[i--] = '\0';
	if (pid == 0)
		pid_string[i--] = '0';
	while (pid > 0)
	{
		pid_string[i--] = (pid % 10) + '0';
		pid /= 10;
	}
	write(1, &pid_string[i + 1], 11 - i);
}

int	main(void)
{
	int	pid;

	write(1, "Server PID: ", 13);
	pid = getpid();
	write_pid(pid);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
}
