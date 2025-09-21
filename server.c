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

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static char	character;
	static int	current_bit;

	(void)context;
	
	if (signal == SIGUSR2)
		character = character | 1;
	
	current_bit++;
	
	if (current_bit == 8)
	{
		if (character == '\0')
			write(1, "\n", 1);
		else
			write(1, &character, 1);
		character = 0;
		current_bit = 0;
	}
	else
	{
		character <<= 1;
	}
	
	// Client'a ACK sinyali gönder
	kill(info->si_pid, SIGUSR1);
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
	int					pid;
	struct sigaction	sa;

	write(1, "Server PID: ", 12);
	pid = getpid();
	write_pid(pid);
	write(1, "\n", 1);

	// sigaction yapısını ayarla
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;

	// Signal handler'ları kaydet
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(1, "Error: sigaction failed\n", 24);
		return (1);
	}

	write(1, "Server is ready to receive messages...\n", 40);
	
	while (1)
		pause();
}