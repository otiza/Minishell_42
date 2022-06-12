/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:16:10 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/15 01:14:56 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_help(void)
{
	ft_putstr_fd("Available commands:\n", 1);
	ft_putstr_fd("echo\ncd\npwd\nexport\nunset\nenv\nexit\n", 1);
}

void	do_echo(t_as *as, t_command *cmd)
{
	int		i;
	int		j;
	char	**str;
	t_as	*l;

	str = cmd->args;
	i = 0;
	j = 0;
	l = as;
	while (str[++i] &&!ft_strncmp(str[i], "-n", 3))
		j = 1;
	while (str[i])
	{
		write(cmd->out, str[i], ft_strlen(str[i]));
		if (str[++i])
			write(cmd->out, " ", 1);
	}
	if (j == 0)
		write(cmd->out, "\n", 1);
	as->exitstat = 0;
}

void	do_pwd(t_as *as, t_command *cmd)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (cmd->args_size > 1)
	{	
		ft_putstr_fd("pwd: too many arguments\n", 1);
		as->exitstat = 1;
	}
	else
	{
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
	}
	free(str);
	as->exitstat = 0;
}

int	ft_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	do_export(t_as *as, t_command *cmd)
{
	int		i;
	char	**str;

	str = cmd->args;
	i = 0;
	if (!str[1])
		ft_printsortlst(as);
	else
		ft_lstupdate(as, str);
}
