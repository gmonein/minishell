/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 18:11:19 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/10 17:58:37 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrstr(char *str, char *find)
{
	while (*str)
	{
		if (!ft_strncmp(str, find, ft_strlen(find)))
			return (str);
		str++;
	}
	return (NULL);
}
