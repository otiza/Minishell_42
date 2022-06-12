/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:40:41 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/15 01:14:45 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_freenv(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env;
	while (tmp->next != NULL)
	{
		tmp = tmp2;
		free(tmp->name);
		free(tmp->str);
		tmp2 = tmp->next;
		free(tmp);
	}
	free(tmp);
}

t_env	*ft_lstnewenv(char *name, char *str)
{
	t_env	*elt;

	elt = (t_env *)malloc(sizeof(*elt));
	if (!(elt))
		return (NULL);
	elt->name = ft_strdup(name);
	elt->str = ft_strdup(str);
	elt->next = NULL;
	return (elt);
}

t_env	*ft_addevnlist(t_env **l, char **evn, char ***env, t_as **as)
{
	char	**str;
	int		i;
	t_env	*tmp;

	i = 0;
	str = ft_split(evn[i], '=');
	ft_addenv_back(l, ft_lstnewenv(str[0], str[1]));
	str = ft_free_split(str);
	tmp = *l;
	while (evn[++i])
	{
		str = ft_split(evn[i], '=');
		ft_addenv_back(l, ft_lstnewenv(str[0], str[1]));
		str = ft_free_split(str);
	}
	*env = env_tochar(tmp);
	*as = init_as();
	return (tmp);
}

t_env	*ft_smllst(t_env *env)
{
	char	*str;
	t_env	*tmp;

	str = env->name;
	tmp = env;
	env = env->next;
	while (env)
	{
		if (ft_memcmp(str, env->name, ft_strlen(str) + 1) < 0)
		{
			tmp = env;
			str = env->name;
		}
		env = env->next;
	}
	return (tmp);
}

void	ft_lstupdatehelp(t_as *as, char **p, char str)
{
	if (ft_strchr(p[0], '+'))
	{
		as->exitstat = 1;
		return ;
	}
	if (str == '+')
		export_join(as, p);
	else
		addnewenv(p, as);
}
