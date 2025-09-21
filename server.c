/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:30:05 by eonen             #+#    #+#             */
/*   Updated: 2025/09/21 18:25:16 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static char		character;
	static int		current_bit;

	(void)context;

	if (sig == SIGUSR2)
		character |= 1;

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
		character <<= 1;

	kill(info->si_pid, SIGUSR1);
}

void	write_pid(int pid)
{
	char	pid_str[12];
	int		i;

	i = 11;
	pid_str[i--] = '\0';
	if (pid == 0)
		pid_str[i--] = '0';
	while (pid > 0)
	{
		pid_str[i--] = (pid % 10) + '0';
		pid /= 10;
	}
	write(1, &pid_str[i + 1], 11 - i);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	write(1, "Server PID: ", 12);
	write_pid(pid);
	write(1, "\n", 1);

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;

	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		write(1, "Error: sigaction failed\n", 24);
	while (1)
		pause();
}
