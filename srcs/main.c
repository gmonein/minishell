/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:18:26 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/10 17:53:38 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signal)
{
	(void)signal;
	if (!g_waiting_child)
	{
		ft_putstr("\n");
		ft_putstr(PROMPT);
	}
	return ;
}

int		ft_getchar(void)
{
	int		res;

	read(1, &res, 1);
	return (res);
}

char	*minishell_read_line(void)
{
	char	*line;

	if (get_next_line(0, &line) == -1)
	{
		ft_putstr_fd("minishell: Impossible to read entry\n", 2);
		exit(EXIT_FAILURE);
	}
	return (line);
}

int		minishell_loop(char **env)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	write(1, PROMPT, strlen(PROMPT));
	while (status)
	{
		if ((line = minishell_read_line()))
		{
			args = minishell_split_line(line);
			status = minishell_execute(args, env);
			free(line);
			free(args);
			ft_putstr(PROMPT);
		}
	}
	return (0);
}

int		main(int argc, char **argv, char **base_env)
{
	char		**env;

	(void)argc;
	(void)argv;
	g_waiting_child = 0;
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	env = dup_env(base_env);
	minishell_loop(env);
	return (0);
}
