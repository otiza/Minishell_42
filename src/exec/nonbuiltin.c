/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:34:44 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/15 01:11:04 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_absolute_path(char **pa, char *cmd)
{
	int			i;
	char		*str;
	char		*tmp;
	int			fd;

	i = 0;
	fd = open(cmd, O_RDONLY);
	if (fd > 0)
		return (ft_strdup(cmd));
	while (pa[i])
	{
		str = ft_strjoin(pa[i], "/");
		tmp = str;
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		fd = open(str, O_RDONLY);
		if (fd > 0)
			return (str);
		free(str);
		i++;
	}
	return (ft_strdup(cmd));
}

void	freepath(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	table = NULL;
}

char	*get_cmd_path(char *str, t_env *env)
{
	char	**path;
	char	*cmd;
	t_env	*env_tmp;

	path = NULL;
	env_tmp = env;
	while (env_tmp)
	{
		if (!(ft_strncmp(env_tmp->name, "PATH", 4)))
			cmd = env_tmp->str;
		env_tmp = env_tmp->next;
	}
	if (cmd)
	{
		path = ft_split(cmd, ':');
		str = get_absolute_path(path, str);
		freepath(path);
	}
	return (str);
}

void	argeror(int argc, char **argv)
{
	(void)argc;
	**argv = 0;
}
