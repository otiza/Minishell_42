/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 22:31:00 by zsidki            #+#    #+#             */
/*   Updated: 2021/10/08 13:17:00 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	j;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	j = 0;
	if (len_dst >= size)
		return (len_src + size);
	else
		len_src += len_dst;
	while (src[j] != '\0' && len_dst < size - 1 && dst != src)
	{
		dst[len_dst] = src[j];
		j++;
		len_dst++;
	}
	dst[len_dst] = '\0';
	return (len_src);
}
