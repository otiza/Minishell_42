/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:56:24 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 18:25:58 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"
#include "../../include/heredoc.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = (struct s_parser *)malloc(sizeof(struct s_parser));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	parser->prev_token = parser->current_token;
	return (parser);
}

int	parser_eat(t_parser *parser, int token_type)
{
	if ((int)(parser->current_token->e_type) == token_type)
	{
		if (parser->prev_token != parser->current_token)
		{
			free(parser->prev_token->value);
			free(parser->prev_token);
		}
		parser->prev_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
	}
	else
	{
		parser->current_token->e_type = TOKEN_ERR;
		g_main.exit_stat = 258;
		return (0);
	}
	return (1);
}

int	ft_perror_pipe(t_parser *parser)
{
	if (parser->current_token->e_type == TOKEN_PIPE)
		return (parser_eat(parser, TOKEN_WORD));
	else if (parser->prev_token->e_type == TOKEN_PIPE
		&& parser->current_token->e_type == TOKEN_EOF)
		return (parser_eat(parser, TOKEN_PIPE));
	return (1);
}

void	parser_parse_err(t_parser *parser, t_as *abstract_syntax)
{
	abstract_syntax->envp = parser->lexer->envp;
	if (parser->current_token->e_type == TOKEN_ERR)
	{
		printf("minishell: syntax error near unexpected token '%s'\n",
			parser->current_token->value);
		free_as(abstract_syntax);
		return ;
	}
	input_heredoc(abstract_syntax);
}

int	is_redirection(int type)
{
	if (type == TOKEN_LESS
		|| type == TOKEN_GREAT
		|| type == TOKEN_MGREAT
		|| type == TOKEN_MLESS)
		return (1);
	return (0);
}
