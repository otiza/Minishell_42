/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:45:43 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/15 01:15:35 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_getbiglst(t_env	*env, t_env *big)
{
	t_env	*tmp;
	char	*c;
	char	*p;

	tmp = NULL;
	p = NULL;
	if (big)
		p = ft_strdup(big->name);
	c = ft_strdup("~~~~~~~~");
	while (env)
	{
		if ((ft_memcmp(c, env->name, ft_strlen(c) + 1) > 0 && !p)
			|| ((p && ft_memcmp(p, env->name, ft_strlen(env->name) + 1) < 0)
				&& ft_memcmp(c, env->name, ft_strlen(env->name) + 1) > 0))
		{
			tmp = env;
			free (c);
			c = ft_strdup(env->name);
		}
		env = env->next;
	}
	free (p);
	free (c);
	return (tmp);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**mycatstr(char *str, int i)
{
	char	**p;
	char	*tmp;

	p = malloc(sizeof(char **) * 3);
	if (i)
	{
		tmp = malloc(i + 2);
		if (str[i - 1] == '+')
			ft_strlcpy(tmp, str, i);
		else
			ft_strlcpy(tmp, str, i + 1);
		p[0] = tmp;
		tmp = malloc(ft_strlen(&str[i] + 2));
		ft_strlcpy(tmp, &str[i + 1], ft_strlen(&str[i]));
		p[1] = tmp;
		p[2] = NULL;
	}
	else
	{
		printf("%d\n", i);
		tmp = malloc(i + 2);
		ft_strlcpy(tmp, str, i + 2);
		p[1] = NULL;
	}
	return (p);
}

int	ft_findc(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	ft_lstupdate(t_as *as, char **str)
{
	int		i;
	char	**p;
	int		j;

	i = 0;
	while (str[++i])
	{
		j = ft_findc(str[i], '=');
		if (j)
		{			
			p = mycatstr(str[i], j);
			if (!ft_isalpha(str[i][0]) && str[i][0] != '_')
				as->exitstat = 1;
			else
				ft_lstupdatehelp(as, p, str[i][j]);
			ft_free_split(p);
		}
	}
}
