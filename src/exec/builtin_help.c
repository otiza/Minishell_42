/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:18:14 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/15 00:54:09 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_env(t_as *as, t_command *cmd)
{
	t_env	*env;

	env = as->env;
	if (cmd->args[1])
	{
		as->exitstat = 127;
		return ;
	}
	while (env != NULL)
	{
		ft_putstr_fd(env->name, cmd->out);
		ft_putchar_fd('=', cmd->out);
		ft_putstr_fd(env->str, cmd->out);
		ft_putchar_fd('\n', cmd->out);
		env = env->next;
	}
	as->exitstat = 0;
}

void	do_unset(t_as *as, t_command *cmd)
{
	char	**str;
	int		l;

	l = 0;
	str = cmd->args;
	if (!str[1])
	{
		return ;
	}
	while (str[++l])
	{
		ft_deletlst(str[l], as);
	}
	as->exitstat = 0;
}

void	do_cd(t_as *as, t_command *cmd)
{
	char	**str;

	str = cmd->args;
	if (str[1] && !(ft_cmp("-", str[1])))
		ft_docdret(as);
	else if (!str[1])
		ft_docdsing(as);
	else if (str[1])
	{
		if (chdir(str[1]) < 0)
		{
			perror("cd");
			as->exitstat = 1;
			return ;
		}
		change_oldpwd(as);
		change_pwd(as);
		as->exitstat = 0;
	}
}

void	ft_exit(t_as *as, t_command *cmd)
{
	char	i;
	char	**l;

	i = as->exitstat;
	if (cmd == NULL)
	{
		ft_asclear(&as->env, &free_env);
		free(as);
		exit(i);
	}
	l = cmd->args;
	if (l[1] && l[2])
	{
		as->exitstat = 1;
		ft_putstr_fd("Invalid Arguments!\n", cmd->out);
		return ;
	}
	else if (l[1])
		i = (char)ft_myatoi(l[1]);
	free(as);
	exit(i);
}

void	envpcast(char ***envp, t_env *env)
{
	freechar(*envp);
	*envp = env_tochar(env);
}
