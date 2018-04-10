/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strduptochar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:58:28 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/10 17:58:29 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strduptochar(char *str, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	res = ft_strsub(str, 0, i);
	return (res);
}
