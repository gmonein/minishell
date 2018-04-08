#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include "libft/includes/libft.h"

#define ALLOC_FAILED	"minishell: allocation error\n"

typedef struct		s_built_in
{
	int				(*fct)(char **, char **);
	const char		*name;
}					t_built_in;

typedef enum		s_built_in_list
{
	CD = 0,
	ENV,
	SETENV,
	UNSETENV,
	EXIT,
	END_BUILTIN
}					e_built_in_list;

char	**get_env_key(char *key, char **env)
{
	int		i;
	int		key_len;

	key_len = ft_strlen(key);
	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (&env[i]);
	return (NULL);
}

int		minishell_exit(char **args, char **env)
{
	(void)args;
	(void)env;
	exit(EXIT_SUCCESS);
}

int		minishell_cd(char **args, char **env)
{
	char		**old_pwd;
	char		**pwd;

	if (!args[1] || args[2])
	{
		errno = EINVAL;
		perror("minishell");
	}
	else if (chdir(args[1]) != 0)
		perror("minishell");
	else
	{
		old_pwd = get_env_key("OLDPWD", env);
		pwd = get_env_key("PWD", env);
		if (!pwd)
			return (0);
		if (old_pwd)
		{
			free(*old_pwd);
			*old_pwd = (char *)ft_memalloc(sizeof(char) * (PATH_MAX + ft_strlen("OLDPWD=")));
			ft_strcpy(*old_pwd, "OLDPWD=");
			ft_strcat(*old_pwd, &(*pwd)[ft_strlen("PWD=")]);
		}
		free(*pwd);
		*pwd = (char *)ft_memalloc(sizeof(char) * (PATH_MAX + ft_strlen("OLDPWD=")));
		ft_strcpy(*pwd, "PWD=");
		getcwd(&(*pwd)[ft_strlen("PWD=")], PATH_MAX);
	}
	return (0);
}

int		minishell_env(char **args, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
	return (0);
}

#define SETENV_USAGE		"usage: setenv FOO value\n"
int		minishell_setenv(char **args, char **env)
{
	int		i;
	char	**res;
	char	**key;

	if (!args[1] || !args[2] || args[3])
	{
		ft_putstr_fd(SETENV_USAGE, 2);
		return (0);
	}
	key = get_env_key(args[1], env);
	if (!key)
	{
		i = -1;
		while (env[++i])
			;
		if (i >= ARG_MAX)
			return (0);
		key = &env[i];
		key[1] = NULL;
	}
	if (*key)
		free(*key);
	*key = ft_memalloc(sizeof(char) * (ft_strlen(args[1]) + 2 + ft_strlen(args[2])));
	ft_strcpy(*key, args[1]);
	ft_strcat(*key, "=");
	ft_strcat(*key, args[2]);
	return (0);
}

#define UNSETENV_USAGE "usage : unsetenv FOO\n"
#define NOT_EXIT " does not exist\n"
int		minishell_unsetenv(char **args, char **env)
{
	char	**key;
	int		i;

	if (!args[1] || args[2])
	{
		ft_putstr_fd(UNSETENV_USAGE, 2);
		return (0);
	}
	key = get_env_key(args[1], env);
	if (!key)
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(NOT_EXIT, 2);
		return (0);
	}
	free(*key);
	i = -1;
	while (key[++i])
		key[i] = key[i + 1];
	return (0);
}

static t_built_in	g_built_in[END_BUILTIN] =
{
	[CD] = {.name = "cd", .fct = minishell_cd},
	[ENV] = {.name = "env", .fct = minishell_env},
	[SETENV] = {.name = "setenv", .fct = minishell_setenv},
	[UNSETENV] = {.name = "unsetenv", .fct = minishell_unsetenv},
	[EXIT] = {.name = "exit", .fct = minishell_exit}
};

int		ft_getchar(void)
{
	int		res;

	read(1, &res, 1);
	return (res);
}

void	*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	void	*new;

	new = (char *)malloc(sizeof(char) * new_size);
	bzero(new, sizeof(char) * new_size);
	memcpy(new, ptr, sizeof(char) * size);
	free(ptr);
	return (new);
}

char	*minishell_read_line(void)
{
	char	*line;

	get_next_line(0, &line);
	return (line);
}

int		is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\a')
		return (1);
	else
		return (0);
}

char	**minishell_split_line(char *line)
{
	char		**res;
	int			nb_word;
	int			i;
	int			j;

	nb_word = 0;
	i = -1;
	while (line[++i])
		if (!is_white_space(line[i]) && (i == 0 || is_white_space(line[i - 1])))
			nb_word++;
	res = (char **)malloc(sizeof(char *) * (nb_word + 1));
	i = -1;
	j = -1;
	while (line[++i])
		if (!is_white_space(line[i]) && (i == 0 || is_white_space(line[i - 1])))
			res[++j] = &line[i];
	res[++j] = NULL;
	i = -1;
	while (line[++i])
		if (is_white_space(line[i]))
			line[i] = '\0';
	return (res);
}

int		minishell_execute(char **args, char **env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	int		i;

	if (!args[0])
		return (1);
	i = -1;
	while (++i < END_BUILTIN)
		if (strcmp(args[0], g_built_in[i].name) == 0)
		{
			g_built_in[i].fct(args, env);
			return (1);
		}
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

#define PROMPT	"> "
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
			write(1, PROMPT, strlen(PROMPT));
		}
	}
	return (0);
}

char	**dup_env(char **env)
{
	char		**res;
	int			i;

	i = -1;
	res = (char **)malloc(sizeof(char *) * (ARG_MAX + 1));
	if (!res)
	{
		ft_putstr_fd(ALLOC_FAILED, 2);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (env[++i])
		res[i] = ft_strdup(env[i]);
	res[i] = NULL;
	return (res);
}

int		main(int argc, char **argv, char **base_env)
{
	char		**env;

	env = dup_env(base_env);
	minishell_loop(env);
}
