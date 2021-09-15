/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:36:36 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 16:12:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	write_byte(char is_usr1, t_client_l *client)
{
	if (is_usr1 == TRUE)
		client->c ^= 0x80 >> client->byte;
	else
		client->c |= 0x80 >> client->byte;
	if (++client->byte == 8)
	{
		if (client->c)
		{
			client->str[client->len] = client->c;
			++client->len;
			if (client->len == client->size)
			{
				client->str = ft_realloc_str(client->str, client->size, \
	client->size * 2);
				client->size *= 2;
			}
		}
		else
		{
			if (write(1, client->str, ft_strlen(client->str)) == -1)
				perror("Write_byte");
			remove_client(client->pid, &g_data.list);
			return ;
		}
		client->c = 0xFF;
		client->byte = 0;
	}
}

t_client_l	*new_client(pid_t pid)
{
	t_client_l	*res;

	res = (t_client_l *)malloc(sizeof(t_client_l));
	if (res == NULL)
		exit (1);
	res->pid = pid;
	res->c = 0xFF;
	res->byte = 0;
	res->size = 64;
	res->len = 0;
	res->str = (char *)malloc(sizeof(char) * res->size);
	if (res->str == NULL)
		exit (1);
	ft_memset(res->str, 0, res->size);
	res->next = NULL;
	return (res);
}

t_client_l	*get_client(pid_t pid, t_client_l **list)
{
	t_client_l	*res;

	res = (*list);
	while (res && res->pid != pid)
		res = res->next;
	if (!res || res->pid != pid)
	{
		res = new_client(pid);
		res->next = (*list);
		(*list) = res;
		return (res);
	}
	return (res);
}

t_client_l	*remove_client(pid_t pid, t_client_l **list)
{
	t_client_l	*tmp;
	t_client_l	*prev;

	tmp = (*list);
	if (tmp != NULL && tmp->pid == pid)
	{
		(*list) = tmp->next;
		free(tmp->str);
		free(tmp);
		return (*list);
	}
	while (tmp != NULL && tmp->pid != pid)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	prev->next = tmp->next;
	free(tmp->str);
	free(tmp);
	return (prev->next);
}
