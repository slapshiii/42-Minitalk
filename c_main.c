/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:04:51 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 19:41:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	sigusr1_handler(int sig)
{
	(void)sig;
	return ;
}

int	send_char(t_client *client, char c)
{
	int	sig;

	while (client->bit < 8)
	{
		if ((c >> (7 - client->bit)) & 0b1)
			sig = SIGUSR2;
		else
			sig = SIGUSR1;
		if (kill(client->s_pid, sig) == -1)
			return (1);
		pause();
		++client->bit;
	}
	client->bit = 0;
	return (0);
}

int	send_msg(t_client *c)
{
	while (c->msg[c->len])
	{
		if (send_char(c, c->msg[c->len]))
			return (1);
		++c->len;
	}
	if (send_char(c, '\0'))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_client	client;
	sig_t		sig_usr1;
	int			res;

	sig_usr1 = signal(SIGUSR1, sigusr1_handler);
	if (ac != 3)
	{
		write(2, "client: usage: server_pid message_to_send.\n", 43);
		return (1);
	}
	client.s_pid = (pid_t)ft_atoi(av[1]);
	client.bit = 0;
	client.len = 0;
	client.msg = av[2];
	if (client.s_pid < 2)
	{
		write(2, "client: error: server_pid is \
suspicious, nothing has been done.\n", 64);
		return (1);
	}
	res = send_msg(&client);
	signal(SIGUSR1, sig_usr1);
	return (res);
}
