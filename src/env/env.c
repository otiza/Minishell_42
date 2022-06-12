/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:09:45 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/15 01:14:51 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_deletlst(char *name, t_as *as)
{
	t_env	*lst;
	t_env	*tmp;

	lst = as->env;
	tmp = NULL;
	while (lst)
	{
		if (!strncmp(name, lst->name, ft_strlen(lst->name) + 1))
			break ;
		tmp = lst;
		lst = lst->next;
	}
	if (!lst)
		return ;
	if (tmp)
		tmp->next = lst->next;
	else
		as->env = lst->next;
	free (lst->str);
	free (lst->name);
	free (lst);
}

char	**ft_free_split(char **d)
{
	int				i;

	i = 0;
	if (d == NULL)
		return (NULL);
	while (d[i])
	{
		if (d[i])
			free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

t_env	*ft_lstfind(t_env *lst, char *name)
{
	while (lst)
	{
		if (!ft_cmp(name, lst->name))
			return (lst);
		else
			lst = lst->next;
	}
	return (NULL);
}

t_env	*ft_lastenv(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_addenv_back(t_env **alst, t_env *new)
{
	t_env	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lastenv(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}
