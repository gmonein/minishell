/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupdoubletab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:58:13 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/10 17:58:17 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**dup_double_tab(char **d_tab)
{
	int		i;
	char	**res;

	i = 0;
	while (d_tab[i])
		i++;
	if (!(res = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (d_tab[i])
	{
		res[i] = ft_strdup(d_tab[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
