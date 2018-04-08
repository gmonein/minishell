/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiputstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 18:50:01 by gmonein           #+#    #+#             */
/*   Updated: 2017/11/04 18:52:48 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

void		ft_multiputstr(char **str)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_putstr(*str);
		str++;
	}
}
