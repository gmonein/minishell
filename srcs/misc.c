/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:17:44 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/10 18:44:06 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t		nb_word;
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

char	**ft_strsplit_c(char *str, char c)
{
	char		**res;
	size_t		nb_word;
	int			i;
	int			j;
	char		*line;

	line = ft_strdup(str);
	nb_word = 0;
	i = -1;
	while (line[++i])
		if (line[i] != c && (i == 0 || line[i - 1] == c))
			nb_word++;
	res = (char **)malloc(sizeof(char *) * (nb_word + 1));
	i = -1;
	j = -1;
	while (line[++i])
		if (line[i] != c && (i == 0 || line[i - 1] == c))
			res[++j] = &line[i];
	res[++j] = NULL;
	i = -1;
	while (line[++i])
		if (line[i] == c)
			line[i] = '\0';
	return (res);
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

int		ft_getchar(void)
{
	int		res;

	read(1, &res, 1);
	return (res);
}
