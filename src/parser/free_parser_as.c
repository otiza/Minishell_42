/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser_as.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:57:21 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/15 04:31:05 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	free_parser(t_parser *parser)
{
	free(parser->lexer);
	free(parser->prev_token->value);
	free(parser->prev_token);
	if (parser->prev_token != parser->current_token)
	{
		free(parser->current_token->value);
		free(parser->current_token);
	}
	free(parser);
}

void	free_as(t_as *root)
{
	int	cs;
	int	as;

	if (root->cmds != NULL)
	{
		cs = root->cmds_size;
		while (cs--)
		{
			as = root->cmds[cs]->args_size;
			while (as--)
				free(root->cmds[cs]->args[as]);
			free(root->cmds[cs]->args);
			while (root->cmds[cs]->redi_size--)
			{
				free(root->cmds[cs]->redi[root->cmds[cs]->redi_size]->file);
				free(root->cmds[cs]->redi[root->cmds[cs]->redi_size]);
			}
			free(root->cmds[cs]->redi);
			free(root->cmds[cs]);
		}
		free(root->cmds);
		root->cmds = NULL;
	}
}
