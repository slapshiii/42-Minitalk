/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:04:33 by user42            #+#    #+#             */
/*   Updated: 2021/09/16 19:44:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

# include <stdio.h>

# define TRUE 1
# define FALSE 0

# define USR1 0
# define USR2 1

enum e_sig
{
	new_int = 0,
	old_int,
	new_usr,
	old_usr1,
	old_usr2
};

typedef struct s_client_l
{
	pid_t				pid;
	char				c;
	size_t				byte;
	char				*str;
	size_t				len;
	size_t				size;
	struct s_client_l	*next;
}	t_client_l;

typedef struct s_minitalk
{
	char				interrupt;
	sigset_t			blockmask;
	struct sigaction	signals[5];
	t_client_l			*list;
}	t_minitalk;

extern t_minitalk	g_data;

t_client_l	*new_client(pid_t pid);
t_client_l	*get_client(pid_t pid, t_client_l **list);
t_client_l	*remove_client(pid_t pid, t_client_l **list);
void		write_byte(char is_usr1, t_client_l *client);
void		read_str(void);

void		*ft_memset(void *s, int c, size_t n);
size_t		ft_strlen(char *str);
char		*ft_itoa(int n, char *str, int base);
char		*realloc_s(char *ptr, size_t prev_size, size_t new_size);

#endif