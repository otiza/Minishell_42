/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:28:44 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/14 19:32:54 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_myatoi(char *str)
{
	unsigned long long	m;
	int					i;
	int					n;

	m = 0;
	n = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		n = -1;
		if (str[++i] == '-')
			ft_error("", 255);
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		m = (m * 10) + (str[i++] - 48);
		if ((m > 9223372036854775807 && n > 0)
			|| (m - 1 > 9223372036854775807 && n < 0))
			ft_error("Invalid Arguments!\n", 255);
	}
	if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		ft_error("Invalid Arguments!\n", 255);
	return (m * n);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	free(tmp->name);
	free(tmp->str);
	free(env);
}

void	ft_asclear(t_env **env, void (*del)(t_env *))
{
	t_env	*help;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->next)
			help = tmp->next;
		else
			help = NULL;
		del(tmp);
		free(tmp);
		tmp = help;
	}
	(*env) = NULL;
}
