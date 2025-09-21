/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:43:28 by eonen             #+#    #+#             */
/*   Updated: 2025/09/21 16:33:40 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <sys/types.h>
# include <unistd.h>

int		ft_atoi(char *str);
void	ack_handler(int sig);
void	send_char(int pid, char c);
int		ft_strlen(char *str);
void	handle_signal(int sig, siginfo_t *info, void *context);
void	write_pid(int pid);

#endif