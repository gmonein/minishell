/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:18:52 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/08 16:37:26 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "libft/includes/libft.h"

# define PROMPT			"$> "
# define ALLOC_FAILED	"minishell: allocation error\n"
# define SETENV_USAGE	"usage: setenv FOO value\n"
# define NO_OLDPWD		"minishell: unable to find OLDPWD in env\n"
# define UNSETENV_USAGE	"usage : unsetenv FOO\n"
# define NOT_EXIT		" does not exist\n"
# define ENV_FULL		"minishell: env is full\n"

typedef struct	s_built_in
{
	int				(*fct)(char **, char **);
	const char		*name;
}				t_built_in;

typedef enum	e_built_in_list
{
	CD = 0,
	ENV,
	SETENV,
	UNSETENV,
	EXIT,
	END_BUILTIN
}				t_built_in_list;

char			**ft_strsplit_c(char *str, char c);
char			**minishell_split_line(char *line);
char			**get_env_key(char *key, char **env);
int				minishell_exit(char **args, char **env);
int				minishell_setenv(char **args, char **env);
char			*minishell_cd_getpath(char **args, char **env);
int				minishell_cd(char **args, char **env);
int				minishell_env(char **args, char **env);
int				minishell_unsetenv(char **args, char **env);
char			*search_executable(char *exec, char **env);
int				minishell_execute_fork(char *exec, char **args, char **env);
int				minishell_launch(char **args, char **env);
int				minishell_execute(char **args, char **env);
int				minishell_loop(char **env);
char			**dup_env(char **env);
void			sig_handler(int signal);
int				main(int argc, char **argv, char **base_env);

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-const-variable"

static const		t_built_in	g_built_in[END_BUILTIN] =
{
	[CD] = {.name = "cd", .fct = minishell_cd},
	[ENV] = {.name = "env", .fct = minishell_env},
	[SETENV] = {.name = "setenv", .fct = minishell_setenv},
	[UNSETENV] = {.name = "unsetenv", .fct = minishell_unsetenv},
	[EXIT] = {.name = "exit", .fct = minishell_exit}
};

# pragma GCC diagnostic pop

#endif
