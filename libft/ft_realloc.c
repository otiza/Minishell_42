/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:30:26 by zsidki            #+#    #+#             */
/*   Updated: 2022/01/02 14:37:30 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mema;

	mema = malloc(size);
	if (!mema)
		return (NULL);
	ft_bzero(mema, size);
	return (mema);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*n_ptr;

	if (ptr)
	{
		if (size)
		{
			n_ptr = ft_memalloc(size);
			if (!n_ptr)
				return (NULL);
			ft_bzero(n_ptr, size);
			ft_memcpy(n_ptr, ptr, size);
		}
		else
		{
			n_ptr = (unsigned char *)malloc(sizeof(ptr));
			if (!n_ptr)
				return (NULL);
		}
		free(ptr);
		return (n_ptr);
	}
	return ((unsigned char *)malloc(sizeof(ptr) * size));
}
