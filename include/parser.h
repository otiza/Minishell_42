/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:11:23 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 19:33:05 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "as.h"
# include "lexer.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*current_token;
	t_token	*prev_token;
}	t_parser;

t_parser	*init_parser(t_lexer *lexer);
int			parser_eat(t_parser *parser, int token_type);
void		parser_parse(t_parser *parser, t_as *abstract_syntax);
t_command	*parser_parse_cmd(t_parser *parser);
char		*parser_parse_args(t_parser *parser);
t_redirect	*parser_parse_redirection(t_parser *parser);
int			ft_perror_pipe(t_parser *parser);
int			is_redirection(int type);
void		parser_parse_err(t_parser *parser, t_as *abstract_syntax);
void		free_parser(t_parser *parser);
void		free_as(t_as *root);

#endif