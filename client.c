/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:29:14 by alaakson          #+#    #+#             */
/*   Updated: 2024/08/02 14:10:10 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, char c, int bit)
{
	if (bit < 8)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(1000);
		send_signal(pid, c, bit + 1);
	}
}

void	send_message(int pid, const char *message)
{
	if (*message)
	{
		send_signal(pid, *message, 0);
		send_message(pid, message + 1);
	}
}

int	main(int argc, char*argv[])
{
	char	*message;
	int		server_pid;

	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		message = argv[2];
		if (message[0] == 0)
		{
			ft_printf ("Empty message not allowed\n");
			return (1);
		}
		send_message(server_pid, message);
		send_signal(server_pid, '\0', 0);
	}
	else
	{
		ft_printf("Enter arguments: ./client <PID> <MESSAGE> \n");
		return (1);
	}
	return (0);
}
