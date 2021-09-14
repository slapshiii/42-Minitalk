/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:36:36 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 19:46:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	write_byte(char is_usr1, t_client_l *client)
{
	if (is_usr1 == TRUE)
		client->c = (client->c << 1) | USR1;
	else
		client->c = (client->c << 1) | USR2;
	++client->byte;
	if (client->byte == 8)
	{
		client->str[client->len] = client->c;
		++client->len;
		if (client->c == '\0')
		{
			write(1, client->str, ft_strlen(client->str));
			remove_client(client->pid, &g_data);
			return ;
		}
		if (client->len == client->size)
		{
			client->size *= 2;
			client->str = ft_realloc_str(client->str, client->size);
		}
		client->c = 0;
		client->byte = 0;
	}
	kill(client->pid, SIGUSR1);
}

t_client_l	*new_client(pid_t pid)
{
	t_client_l	*res;

	res = (t_client_l *)malloc(sizeof(t_client_l));
	if (res == NULL)
		exit (1);
	res->pid = pid;
	res->c = 0;
	res->byte = 0;
	res->size = 16;
	res->len = 0;
	res->str = (char *)malloc(sizeof(char) * res->size);
	if (res->str == NULL)
		exit (1);
	res->next = NULL;
	return (res);
}

t_client_l	*get_client(pid_t pid, t_minitalk *data)
{
	t_client_l	*res;

	if (data->list == NULL)
	{
		data->list = new_client(pid);
		return (data->list);
	}
	res = data->list;
	while (res->pid != pid && res->next)
		res = res->next;
	if (res->pid != pid)
	{
		res->next = new_client(pid);
		return (res->next);
	}
	return (res);
}

t_client_l	*remove_client(pid_t pid, t_minitalk *data)
{
	t_client_l	*res;
	t_client_l	*prev;

	res = data->list;
	if (res->pid == pid)
	{
		data->list = res->next;
		free(res->str);
		free(res);
		return (data->list);
	}
	while (res && res->pid != pid)
	{
		prev = res;
		res = res->next;
	}
	if (res->pid == pid)
	{
		prev->next = res->next;
		free(res->str);
		free(res);
		return (prev->next);
	}
	else
		return (NULL);
}
