/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:18:11 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/08 16:40:34 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		minishell_unsetenv(char **args, char **env)
{
	char	**key;
	int		i;

	if (!args[1] || args[2])
	{
		ft_putstr_fd(UNSETENV_USAGE, 2);
		return (1);
	}
	key = get_env_key(args[1], env);
	if (!key)
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(NOT_EXIT, 2);
		return (1);
	}
	free(*key);
	i = -1;
	while (key[++i])
		key[i] = key[i + 1];
	return (1);
}

int		minishell_env(char **args, char **env)
{
	int		i;

	if (args[1])
		return (1);
	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
	return (1);
}

char	**minishell_setenv_find_place(char **env)
{
	int		i;
	char	**key;

	i = -1;
	while (env[++i])
		;
	if (i >= ARG_MAX)
	{
		ft_putstr_fd(ENV_FULL, 2);
		return (NULL);
	}
	key = &env[i];
	key[1] = NULL;
	return (key);
}

int		minishell_setenv(char **args, char **env)
{
	char	**key;

	if (!args[1] || !args[2] || args[3])
	{
		ft_putstr_fd(SETENV_USAGE, 2);
		return (1);
	}
	key = get_env_key(args[1], env);
	if (!key)
		key = minishell_setenv_find_place(env);
	if (!key)
		return (1);
	if (*key)
		free(*key);
	*key = ft_memalloc(sizeof(char)
			* (ft_strlen(args[1]) + 2 + ft_strlen(args[2])));
	ft_strcpy(*key, args[1]);
	ft_strcat(*key, "=");
	ft_strcat(*key, args[2]);
	return (1);
}
