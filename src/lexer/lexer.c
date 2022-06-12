/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:15:56 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 18:41:37 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/heredoc.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = malloc(1 * sizeof(struct s_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer-> i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
	{
		lexer_advance(lexer);
	}
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	int	is_heredoc;

	is_heredoc = 0;
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
			lexer_skip_whitespace(lexer);
		else if (is_heredoc)
		{
			is_heredoc = 0;
			return (lexer_collect_hered(lexer));
		}
		else if (lexer->c == '<' || lexer->c == '>')
			return (lexer_collect_redirection(lexer, &is_heredoc));
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer,
					init_token(TOKEN_PIPE, ft_strdup("|"))));
		else
			return (lexer_collect_word(lexer));
	}
	return (init_token(TOKEN_EOF, ft_strdup("newline")));
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}
