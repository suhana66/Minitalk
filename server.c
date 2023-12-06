/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:16:40 by susajid           #+#    #+#             */
/*   Updated: 2023/12/14 15:33:06 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	bitsignal_handler(int sig);
static int	find_bit_place(int n);

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Process ID: %d\n", getpid());
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = bitsignal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

static void	bitsignal_handler(int sig)
{
	static char	msg_c = 0;
	static int	count = MAX_BIT_INDEX;

	if (sig == SIGUSR1)
		msg_c += find_bit_place(count);
	if (!count)
	{
		ft_printf("%c", msg_c);
		msg_c = 0;
		count = MAX_BIT_INDEX;
	}
	else
		count--;
}

static int	find_bit_place(int n)
{
	int	result;

	result = 1;
	while (n--)
		result *= 2;
	return (result);
}
