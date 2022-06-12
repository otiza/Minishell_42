/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:49:42 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/11 17:07:43 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"
#include "../../include/heredoc.h"

static char	*lexer_collect_dquote_hrdc(t_lexer *lexer, int *err)
{
	char	*new;
	int		i;

	new = malloc(2 * sizeof(char));
	*new = lexer->c;
	lexer_advance(lexer);
	i = 1;
	while (lexer->c != '\0')
	{
		new = ft_realloc(new, sizeof(char) * i + 2);
		new[i++] = lexer->c;
		if (lexer->c == '"')
			break ;
		lexer_advance(lexer);
	}
	new[i] = '\0';
	if (lexer->c != '"')
		*err = 1;
	lexer_advance(lexer);
	return (new);
}

static char	*lexer_collect_squote_hrdc(t_lexer *lexer, int *err)
{
	char	*new;
	int		i;

	new = malloc(2 * sizeof(char));
	*new = lexer->c;
	lexer_advance(lexer);
	i = 1;
	while (lexer->c != '\0')
	{
		new = ft_realloc(new, sizeof(char) * i + 2);
		new[i++] = lexer->c;
		if (lexer->c == '\'')
			break ;
		lexer_advance(lexer);
	}
	new[i] = '\0';
	if (lexer->c != '\'')
		*err = 1;
	lexer_advance(lexer);
	return (new);
}

static char	*lexer_collect_id_hrdc(t_lexer *lexer)
{
	char	*new;
	int		i;

	new = malloc(1 * sizeof(char));
	*new = 0;
	i = 0;
	while (is_id(lexer->c))
	{
		new = ft_realloc(new, sizeof(char) * i + 2);
		new[i++] = lexer->c;
		lexer_advance(lexer);
	}
	new[i] = '\0';
	return (new);
}

static t_token	*lexer_collect_hered_2(t_lexer *lexer, char *value, char *s)
{
	int	err;

	value = malloc(1 * sizeof(char));
	value[0] = '\0';
	err = 0;
	while (is_word(lexer->c))
	{
		if (lexer->c == '"')
			s = lexer_collect_dquote_hrdc(lexer, &err);
		else if (lexer->c == '\'')
			s = lexer_collect_squote_hrdc(lexer, &err);
		else
			s = lexer_collect_id_hrdc(lexer);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		if (s)
			free(s);
		if (err)
		{
			free(value);
			return (init_token(TOKEN_ERR, ft_strdup("Quotes not closed")));
		}
	}
	return (init_token(TOKEN_WORD, value));
}

t_token	*lexer_collect_hered(t_lexer *lexer)
{
	char	*value;
	char	*s;
	char	redi;

	value = NULL;
	s = NULL;
	redi = lexer->c;
	lexer_advance(lexer);
	if (lexer->c != redi && redi == '<')
		return (init_token(TOKEN_EOF, ft_strdup("<")));
	if (lexer->c != redi && redi == '>')
		return (init_token(TOKEN_EOF, ft_strdup(">")));
	if (lexer->c == redi && redi == '<')
		return (init_token(TOKEN_EOF, ft_strdup("<<")));
	if (lexer->c == redi && redi == '>')
		return (init_token(TOKEN_EOF, ft_strdup(">>")));
	lexer->i -= 1;
	lexer->c = lexer->contents[lexer->i];
	return (lexer_collect_hered_2(lexer, value, s));
}
