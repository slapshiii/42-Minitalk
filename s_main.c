/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:02:38 by user42            #+#    #+#             */
/*   Updated: 2021/09/16 22:21:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <signal.h>

t_minitalk	g_data;

void	clean_exit(int sig)
{
	t_client_l	*res;
	t_client_l	*tofree;

	res = (g_data.list);
	while (res)
	{
		tofree = res;
		res = res->next;
		free(tofree->str);
		free(tofree);
		tofree = NULL;
	}
	sigaction(SIGINT, &g_data.signals[old_int], NULL);
	sigaction(SIGUSR1, &g_data.signals[old_usr1], NULL);
	sigaction(SIGUSR2, &g_data.signals[old_usr2], NULL);
	exit(sig);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_data.interrupt = TRUE;
	clean_exit(0);
}

void	sigusr_handler(int sig, siginfo_t *info, void *context)
{
	t_client_l	*c;

	(void)context;
	c = get_client(info->si_pid, &(g_data.list));
	if (sig == SIGUSR1)
		write_byte(TRUE, c);
	else
		write_byte(FALSE, c);
	if (kill(info->si_pid, SIGUSR1))
		clean_exit(1);
}

void	init(t_minitalk *data)
{
	ft_memset(data->signals, 0, sizeof(struct sigaction) * 5);
	data->interrupt = FALSE;
	data->list = NULL;
	data->signals[new_int].sa_handler = sigint_handler;
	data->signals[new_usr].sa_flags = SA_SIGINFO;
	data->signals[new_usr].sa_sigaction = sigusr_handler;
	if (sigaction(SIGINT, &data->signals[new_int],
			&data->signals[old_int]) == -1
		|| sigaction(SIGUSR1, &data->signals[new_usr],
			&data->signals[old_usr1]) == -1
		|| sigaction(SIGUSR2, &data->signals[new_usr],
			&data->signals[old_usr2]) == -1
	)
		clean_exit(1);
}

int	main(void)
{
	char		str[10];

	init(&g_data);
	ft_itoa((int)getpid(), str, 10);
	if (write(2, str, ft_strlen(str)) == -1
		|| (write(2, "\n", 1) == -1))
		return (1);
	while (g_data.interrupt == FALSE)
		pause();
}
