/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:29:08 by alaakson          #+#    #+#             */
/*   Updated: 2024/08/05 19:39:18 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig)
{
	static char	g_char = 0;
	static int	g_bit = 0;

	g_char |= (sig == SIGUSR2) << g_bit;
	g_bit++;
	if (g_bit == 8)
	{
		if (g_char == '\0')
		{
			ft_printf("\n");
		}
		else
		{
			write (1, &g_char, 1);
		}
		g_char = 0;
		g_bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf ("Hello and Welcome To The Server\n");
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("The Server PID: %d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}
