/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:04:51 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 16:06:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	g_client;

void	sigusr_handler(int sig)
{
	int	is_finished;

	is_finished = 0;
	if (sig == SIGUSR1)
		is_finished = send_char(&g_client);
	if (is_finished)
	{
		exit(0);
	}
}

int	send_eof(pid_t pid)
{
	static int	bit = -1;

	if (++bit != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			exit(1);
		return (FALSE);
	}
	return (TRUE);
}

int	send_char(t_client *client)
{
	if (client->msg[client->bit / 8])
	{
		if (client->msg[client->bit / 8] & (0x80 >> (client->bit % 8)))
		{
			if (kill(client->s_pid, SIGUSR2) == -1)
				exit(1);
		}
		else if (kill(client->s_pid, SIGUSR1) == -1)
			exit(1);
		++client->bit;
		return (FALSE);
	}
	if (!send_eof(client->s_pid))
		return (FALSE);
	free(client->msg);
	return (TRUE);
}

int	main(int ac, char **av)
{
	sig_t		sig_usr1;

	sig_usr1 = signal(SIGUSR1, sigusr_handler);
	if (ac != 3 || !ft_isnum(av[1]))
	{
		write(2, "client: usage: server_pid message_to_send.\n", 43);
		return (1);
	}
	g_client.interrupt = FALSE;
	g_client.s_pid = (pid_t)ft_atoi(av[1]);
	g_client.bit = 0;
	g_client.msg = ft_strdup(av[2]);
	send_char(&g_client);
	while (g_client.interrupt == FALSE)
		pause();
}
