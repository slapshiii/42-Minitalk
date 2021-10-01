/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phnguyen <phnguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:04:51 by user42            #+#    #+#             */
/*   Updated: 2021/10/01 15:44:57 by phnguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	g_client;

void	clean_exit(int sig)
{
	if (g_client.msg)
		free(g_client.msg);
	exit(sig);
}

void	sigusr_handler(int sig)
{
	int	is_finished;

	usleep(2);
	is_finished = 0;
	if (sig == SIGUSR1)
		is_finished = send_char(&g_client);
	if (is_finished)
	{
		clean_exit(0);
	}
}

int	send_eof(pid_t pid)
{
	if (g_client.lastbit < 8)
	{
		++g_client.lastbit;
		if (kill(pid, SIGUSR1) == -1)
			clean_exit(1);
		return (FALSE);
	}
	pause();
	return (TRUE);
}

int	send_char(t_client *client)
{
	int	sig;

	if (client->msg[client->bit / 8])
	{
		if (client->msg[client->bit / 8] & (0x80 >> (client->bit % 8)))
			sig = SIGUSR2;
		else
			sig = SIGUSR1;
		++client->bit;
		if (kill(client->s_pid, sig) == -1)
			clean_exit(1);
		return (FALSE);
	}
	if (!send_eof(client->s_pid))
		return (FALSE);
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
	g_client.lastbit = 0;
	g_client.msg = ft_strdup(av[2]);
	send_char(&g_client);
	while (g_client.interrupt == FALSE)
		pause();
}
