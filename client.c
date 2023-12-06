/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:04:53 by susajid           #+#    #+#             */
/*   Updated: 2023/12/12 11:55:50 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	send_str(pid_t pid, char *msg);
static int	send_signal(pid_t pid, int sig);

int	main(int argc, char **argv)
{
	int	pid;
	int	res;

	if (argc != 3)
	{
		ft_printf("Error: client expects 3 arguments, have %d arguments\n"
			"Usage: ./client <pid> <message>\n",
			argc);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	res = send_signal(pid, 0);
	if (res)
		return (res);
	return (send_str(pid, argv[2]));
}

static int	send_str(pid_t pid, char *msg)
{
	int	size_char;
	int	res;

	while (*msg)
	{
		size_char = MAX_BIT_INDEX;
		while (size_char >= 0)
		{
			if ((*msg >> size_char & 1) == 0)
				res = send_signal(pid, SIGUSR2);
			else
				res = send_signal(pid, SIGUSR1);
			if (res)
				return (res);
			usleep(100);
			size_char--;
		}
		msg++;
	}
	return (0);
}

static int	send_signal(pid_t pid, int sig)
{
	if (pid <= 0)
	{
		ft_printf("Error: Forbidden function"
			" (trying to send signal to multiple processes)\n");
		return (2);
	}
	if (kill(pid, sig) == -1)
	{
		ft_printf("Error: Cannot send signal to given process ID\n");
		return (3);
	}
	return (0);
}
