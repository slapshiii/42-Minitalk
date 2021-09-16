/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:04:36 by user42            #+#    #+#             */
/*   Updated: 2021/09/16 20:56:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

# include <stdio.h>

# define TRUE 1
# define FALSE 0

# define USR1 0
# define USR2 1

typedef struct s_client
{
	char	interrupt;
	pid_t	s_pid;
	int		bit;
	int		lastbit;
	char	*msg;
}	t_client;

extern t_client	g_client;

int		send_char(t_client *client);
int		send_eof(pid_t pid);

int		is_whitespace(char c);
int		ft_atoi(const char *s);
int		ft_isnum(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

#endif