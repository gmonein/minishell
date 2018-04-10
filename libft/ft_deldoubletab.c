/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:12:21 by gmonein           #+#    #+#             */
/*   Updated: 2018/04/10 19:15:17 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_deldoubletab(void ***tab)
{
	int		i;

	i = 0;
	if (*tab)
	{
		while ((*tab)[i])
			ft_memdel(&((*tab)[i]));
		*tab = NULL;
		free(*tab);
		*tab = NULL;
	}
}
