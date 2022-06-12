/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:41:57 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/14 22:40:31 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h" 

void	ft_out(int *i, t_redirect *redi)
{
	if (redi->e_type == 1)
		*i = open(redi->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (redi->e_type == 2)
		*i = open(redi->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
}

void	ft_in(int *i, t_redirect *redi)
{
	*i = open(redi->file, O_RDONLY);
}

void	get_outredi(int *out, int *in, t_command *cmd)
{
	size_t	i;

	i = 0;
	*in = 0;
	while (++i <= cmd->redi_size)
	{
		if (cmd->redi[i - 1]->e_type == 1 || cmd->redi[i - 1]->e_type == 2)
			ft_out(out, cmd->redi[i -1]);
		if (cmd->redi[i - 1]->e_type == 0 || cmd->redi[i - 1]->e_type == 3)
			ft_in(in, cmd->redi[i -1]);
	}
}

void	get_redi(t_as *as)
{
	size_t	i;

	i = 0;
	if (as->cmds_size != 0 && as->cmds)
	{
		while (++i <= as->cmds_size)
		{
			if (as->cmds[i - 1]->redi_size == 0)
				continue ;
			else
			{
				get_outredi(&(as->cmds[i - 1]->out),
					&(as->cmds[i - 1]->in), as->cmds[i - 1]);
			}
		}
	}
}

void	freechar(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i++]);
	}
	free(envp);
}
