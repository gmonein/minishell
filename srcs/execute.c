/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:18:17 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/10 19:38:43 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_executable(char *exec, char **env)
{
	char	**key;
	char	**path;
	char	*buf;
	int		i;
	char	*res;

	if (!(key = get_env_key("PATH", env)))
		return (ft_strdup(exec));
	buf = ft_memalloc(sizeof(char) * (PATH_MAX + 1));
	path = ft_strsplit(*key, ':');
	i = -1;
	res = exec;
	while (path[++i])
	{
		ft_strcat(ft_strcat(ft_strcpy(buf, path[i]), "/"), exec);
		if (!access(buf, X_OK) && (res = buf) != NULL)
			break ;
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (ft_strcpy(buf, res));
}

int		minishell_execute_fork(char *exec_name, char **args, char **env)
{
	struct stat		filestat;

	if (stat(exec_name, &filestat))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	if (!(filestat.st_mode & S_IXUSR))
	{
		errno = EACCES;
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	if (execve(exec_name, args, env) == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int		minishell_launch(char **args, char **env)
{
	char	*exec_name;
	pid_t	pid;
	int		status;

	exec_name = search_executable(args[0], env);
	pid = fork();
	if (pid == 0)
		minishell_execute_fork(exec_name, args, env);
	else if (pid < 0)
	{
		perror("minishell");
		exit(EXIT_SUCCESS);
	}
	else
	{
		g_waiting_child = 1;
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		g_waiting_child = 0;
	}
	free(exec_name);
	return (1);
}

int		minishell_execute(char **args, char **env)
{
	int		i;

	if (!args[0])
		return (1);
	i = -1;
	while (++i < END_BUILTIN)
		if (strcmp(args[0], g_built_in[i].name) == 0)
			return (g_built_in[i].fct(args, env));
	return (minishell_launch(args, env));
}
