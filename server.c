/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:06:36 by eonen             #+#    #+#             */
/*   Updated: 2025/09/22 18:36:22 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static char	character;
	static int	current_bit;

	(void)context;
	if (sig == SIGUSR2)
		character |= (1 << (7-current_bit));
	current_bit++;
	if (current_bit == 8)
	{
		write(1,&character,1);
		character = 0;
		current_bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	write_pid(int pid)
{
	char	pid_buf[12];
	int		i;
	int		j;

	i = 11;
	pid_buf[i] = '\0';
	i--;
	if (pid == 0)
		pid_buf[i--] = '0';
	while (pid > 0)
	{
		pid_buf[i] = (pid % 10) + '0';
		pid /= 10;
		i--;
	}
	j = i + 1;
	while (pid_buf[j])
	{
		write(1, &pid_buf[j], 1);
		j++;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sigact;

	pid = getpid();
	write(1, "Server PID: ", 12);
	write_pid(pid);
	write(1, "\n", 1);
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	sigact.sa_sigaction = handle_signal;
	sigact.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &sigact, NULL) == -1 || sigaction(SIGUSR2, &sigact,
			NULL) == -1)
		write(1, "Error: sigaction failed\n", 24);
	while (1)
		pause();
}
