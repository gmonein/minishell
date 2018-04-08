/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:18:02 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/08 16:19:12 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*minishell_cd_getpath(char **args, char **env)
{
	char		*path;
	char		**old_pwd;

	if (!args[1] || args[2])
	{
		errno = EINVAL;
		perror("minishell");
		return (NULL);
	}
	path = args[1];
	if (!ft_strcmp(args[1], "-"))
	{
		old_pwd = get_env_key("OLDPWD", env);
		if (!old_pwd)
		{
			ft_putstr_fd(NO_OLDPWD, 2);
			return (NULL);
		}
		path = &(*old_pwd)[ft_strlen("OLDPWD=")];
	}
	return (path);
}

int		minishell_cd(char **args, char **env)
{
	char		**pwd;
	char		*path;
	char		buf[PATH_MAX];

	path = minishell_cd_getpath(args, env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		perror("minishell");
	else
	{
		pwd = get_env_key("PWD", env);
		if (!pwd)
			return (1);
		minishell_setenv(
		(char *[]){"setenv", "OLDPWD", &(*pwd)[ft_strlen("PWD=")], NULL}, env);
		getcwd(buf, PATH_MAX);
		minishell_setenv(
		(char *[]){"setenv", "PWD", buf, NULL}, env);
	}
	return (1);
}
