/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 19:38:02 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/11 16:50:34 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/as.h"

t_as	*init_as(void)
{
	t_as	*as;

	as = malloc(1 * sizeof(struct s_as));
	as->sigint = 0;
	as->exitstat = 0;
	return (as);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(1 * sizeof(struct s_command));
	cmd->args = NULL;
	cmd->args_size = 0;
	cmd->redi = NULL;
	cmd->redi_size = 0;
	cmd->in = 0;
	cmd->out = 1;
	return (cmd);
}
