/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:52:54 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 18:27:20 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"
#include "../../include/heredoc.h"

void	parser_parse(t_parser *parser, t_as *abstract_syntax)
{
	t_command	*cmd;

	ft_perror_pipe(parser);
	abstract_syntax->cmds = malloc(1 * sizeof(struct t_command *));
	abstract_syntax->cmds_size = 0;
	cmd = parser_parse_cmd(parser);
	abstract_syntax->cmds[0] = cmd;
	abstract_syntax->cmds_size += 1;
	while (parser->current_token->e_type == TOKEN_PIPE
		&& parser->current_token->e_type != TOKEN_EOF)
	{
		parser_eat(parser, TOKEN_PIPE);
		ft_perror_pipe(parser);
		cmd = parser_parse_cmd(parser);
		if (cmd)
		{
			abstract_syntax->cmds_size += 1;
			abstract_syntax->cmds = ft_realloc(
					abstract_syntax->cmds,
					abstract_syntax->cmds_size * sizeof(t_command *));
			abstract_syntax->cmds[abstract_syntax->cmds_size - 1] = cmd;
		}
	}
	parser_parse_err(parser, abstract_syntax);
}

static void	parse_cmd_arg(t_parser *parser, t_command *cmd)
{
	cmd->args_size += 1;
	if (!cmd->args)
		cmd->args = malloc(1 * sizeof(char *));
	else
		cmd->args = ft_realloc(cmd->args, cmd->args_size * sizeof(char *));
	cmd->args[cmd->args_size - 1] = parser_parse_args(parser);
	if (cmd->args[cmd->args_size - 1] == NULL)
		cmd->args = ft_realloc(cmd->args, --cmd->args_size * sizeof(char *));
}

t_command	*parser_parse_cmd(t_parser *parser)
{
	t_command	*cmd;

	cmd = init_command();
	while (parser->current_token->e_type != TOKEN_PIPE
		&& parser->current_token->e_type != TOKEN_EOF
		&& parser->current_token->e_type != TOKEN_ERR)
	{
		if (is_redirection(parser->current_token->e_type))
		{
			cmd->redi_size += 1;
			if (!cmd->redi)
				cmd->redi = malloc(1 * sizeof(t_redirect *));
			else
				cmd->redi = ft_realloc(cmd->redi, cmd->redi_size
						* sizeof(t_redirect *));
			cmd->redi[cmd->redi_size - 1] = parser_parse_redirection(parser);
		}
		else
			parse_cmd_arg(parser, cmd);
	}
	cmd->args = ft_realloc(cmd->args, (cmd->args_size + 1) * sizeof(char *));
	cmd->args[cmd->args_size] = NULL;
	return (cmd);
}

char	*parser_parse_args(t_parser *parser)
{
	char	*arg;

	if (!parser->current_token->value)
		arg = NULL;
	else
		arg = ft_strdup(parser->current_token->value);
	parser_eat(parser, TOKEN_WORD);
	return (arg);
}

t_redirect	*parser_parse_redirection(t_parser *parser)
{
	t_redirect	*redi;

	redi = malloc(sizeof(struct s_redirect));
	if (parser->current_token->e_type == TOKEN_LESS)
		redi->e_type = INPUT;
	if (parser->current_token->e_type == TOKEN_GREAT)
		redi->e_type = OUTPUT;
	if (parser->current_token->e_type == TOKEN_MLESS)
		redi->e_type = HEREDOC;
	if (parser->current_token->e_type == TOKEN_MGREAT)
		redi->e_type = APPEND;
	parser_eat(parser, parser->current_token->e_type);
	if (!parser->current_token->value)
		redi->file = NULL;
	else
		redi->file = ft_strdup(parser->current_token->value);
	parser_eat(parser, TOKEN_WORD);
	return (redi);
}
