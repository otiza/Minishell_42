/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_quote_redi_id.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:53:41 by zsidki            #+#    #+#             */
/*   Updated: 2022/01/26 22:59:06 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

char	*lexer_collect_single_quote(t_lexer *lexer, int *err)
{
	char	*new;
	int		i;

	lexer_advance(lexer);
	new = malloc(1 * sizeof(char));
	*new = 0;
	i = 0;
	while (lexer->c != '\'' && lexer->c != '\0')
	{
		new = ft_realloc(new, sizeof(char) * i + 2);
		new[i++] = lexer->c;
		lexer_advance(lexer);
	}
	new[i] = '\0';
	if (lexer->c != '\'')
		*err = 1;
	lexer_advance(lexer);
	return (new);
}

char	*lexer_collect_double_quote(t_lexer *lexer, int *err)
{
	char	*new;
	int		i;

	lexer_advance(lexer);
	new = malloc(1 * sizeof(char));
	*new = 0;
	i = 0;
	while (lexer->c != '"' && lexer->c != '\0')
	{
		if (lexer->c == '$')
			new = replace_environment(lexer, new, &i);
		else
		{
			new = ft_realloc(new, sizeof(char) * i + 2);
			new[i++] = lexer->c;
			lexer_advance(lexer);
		}
	}
	new[i] = '\0';
	if (lexer->c != '"')
		*err = 1;
	lexer_advance(lexer);
	return (new);
}

t_token	*lexer_collect_redirection(t_lexer *lexer, int *is_heredoc)
{
	char	redirection;

	redirection = lexer->c;
	lexer_advance(lexer);
	if (lexer->c != redirection && redirection == '<')
		return (init_token(TOKEN_LESS, ft_strdup("<")));
	if (lexer->c != redirection && redirection == '>')
		return (init_token(TOKEN_GREAT, ft_strdup(">")));
	if (lexer->c == redirection && redirection == '<')
	{	
		*is_heredoc = 1;
		return (lexer_advance_with_token(lexer,
				init_token(TOKEN_MLESS, ft_strdup("<<"))));
	}
	if (lexer->c == redirection && redirection == '>')
		return (lexer_advance_with_token(lexer,
				init_token(TOKEN_MGREAT, ft_strdup(">>"))));
	return (init_token(TOKEN_EOF, ft_strdup("\0")));
}

int	is_id(char c)
{
	if (c != '<' && c != '>' && c != '|'
		&& c != ' ' && c != '\n' && c != '\0'
		&& c != '\t' && c != '"' && c != '\'')
		return (1);
	return (0);
}

char	*lexer_collect_id(t_lexer *lexer)
{
	char	*new;
	int		i;

	new = malloc(1 * sizeof(char));
	*new = 0;
	i = 0;
	while (is_id(lexer->c))
	{
		if (lexer->c == '$')
			new = replace_environment(lexer, new, &i);
		else
		{
			new = ft_realloc(new, sizeof(char) * i + 2);
			new[i++] = lexer->c;
			lexer_advance(lexer);
		}
	}
	new[i] = '\0';
	return (new);
}
