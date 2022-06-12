/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:09:45 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/15 01:15:20 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	addnewenv(char	**p, t_as *as)
{
	t_env	*env;
	t_env	*tmp;

	env = ft_lstfind(as->env, p[0]);
	if (env)
	{
		free (env->str);
		if (p[1])
			env->str = ft_strdup(p[1]);
		else
			env->str = ft_strdup("");
	}
	else
	{
		if (p[1])
			env = ft_lstnewenv(p[0], p[1]);
		else
			env = ft_lstnewenv(p[0], "");
		tmp = ft_lastenv(as->env);
		ft_addenv_back(&as->env, env);
	}
}

void	export_join(t_as *as, char **p)
{
	char	*str;
	char	*tmp;
	t_env	*env;

	env = ft_lstfind(as->env, p[0]);
	if (env)
	{
		if (p[1])
			str = ft_strdup(p[1]);
		else
			str = ft_strdup("");
		tmp = ft_strjoin(env->str, str);
		free (env->str);
		free (str);
		env->str = tmp;
	}
	else
		addnewenv(p, as);
}

void	ft_printsortlst(t_as *as)
{
	t_env	*tmp;

	tmp = NULL;
	while (1)
	{
		tmp = ft_getbiglst(as->env, tmp);
		write(1, "declare -x ", 11);
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=\"", 2);
		write(1, tmp->str, ft_strlen(tmp->str));
		write(1, "\"\n", 2);
		if (!ft_cmp(tmp->name, ft_smllst(as->env)->name))
			break ;
	}
}

int	listln(t_env *env)
{
	int		l;
	t_env	*tmp;

	l = 0;
	tmp = env;
	while (tmp->next != NULL)
	{
		l++;
		tmp = tmp->next;
	}
	return (l);
}

char	**env_tochar(t_env	*env)
{
	char	**envp;
	char	*en;
	t_env	*tmp;
	int		i;

	tmp = env;
	envp = malloc(sizeof(char *) * (listln(env) + 2));
	i = 0;
	while (i <= listln(env))
	{
		en = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(en, tmp->str);
		free(en);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
