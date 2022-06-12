/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 22:23:12 by zsidki            #+#    #+#             */
/*   Updated: 2019/10/26 07:44:12 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*s1;
	char			*s2;

	s1 = (char *)dst;
	s2 = (char *)src;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	while (n > i)
	{
		s1[i] = s2[i];
		i++;
	}
	return (s1);
}
