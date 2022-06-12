/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 22:35:53 by zsidki            #+#    #+#             */
/*   Updated: 2021/10/09 11:45:36 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*tab;

	count = 0;
	tab = 0;
	if (!s)
		return (0);
	tab = (char *)malloc((len + 1) * sizeof(char));
	if (!(tab))
		return (NULL);
	while (len > 0 && s[start + count] && ft_strlen(s) > start)
	{
		tab[count] = s[start + count];
		count++;
		len--;
	}
	tab[count] = '\0';
	return (tab);
}
