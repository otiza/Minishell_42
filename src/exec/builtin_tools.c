/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:24:19 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/14 19:48:45 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_oldpwd(t_as *as)
{
	char	*str;
	t_env	*oldpwd;

	oldpwd = ft_lstfind(as->env, "OLDPWD");
	str = oldpwd->str;
	free (str);
	str = getcwd(NULL, 0);
	if (!(str))
		return ;
	oldpwd->str = ft_strdup(ft_lstfind(as->env, "PWD")->str);
	free (str);
}

void	change_pwd(t_as *as)
{
	char	*str;
	t_env	*pwd;

	pwd = ft_lstfind(as->env, "PWD");
	str = pwd->str;
	free (str);
	str = getcwd(NULL, 0);
	if (!(str))
		return ;
	pwd->str = ft_strdup(str);
	free (str);
}

void	ft_docdret(t_as *as)
{
	t_env	*lst;
	char	*src;

	lst = ft_lstfind(as->env, "OLDPWD");
	if (lst)
	{
		src = ft_strdup(lst->str);
		change_oldpwd(as);
		chdir(src);
		free(src);
		change_pwd(as);
		as->exitstat = 0;
	}
	else
		as->exitstat = 1;
}

void	ft_docdsing(t_as *as)
{
	t_env	*lst;
	char	*src;

	lst = ft_lstfind(as->env, "HOME");
	if (lst)
	{
		src = ft_strdup(lst->str);
		change_oldpwd(as);
		chdir(src);
		free(src);
		change_pwd(as);
		as->exitstat = 0;
	}
	else
		as->exitstat = 1;
}

void	ft_error(char *s, int i)
{
	ft_putstr_fd(s, 1);
	exit(i);
}
