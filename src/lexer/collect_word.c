/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 09:21:02 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 18:30:55 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	is_word(char c)
{
	if (c != '<' && c != '>' && c != '|'
		&& c != ' ' && c != '\n' && c != '\0'
		&& c != '\t')
		return (1);
	return (0);
}

int	lexer_collect_word_main(t_lexer *lexer, char **s,
			char **value, int *is_id)
{
	int	err;

	err = 0;
	if (lexer->c == '"')
		*s = lexer_collect_double_quote(lexer, &err);
	else if (lexer->c == '\'')
		*s = lexer_collect_single_quote(lexer, &err);
	else
	{
		*s = lexer_collect_id(lexer);
		*is_id = 1;
	}
	*value = ft_realloc(*value, (ft_strlen(*value) + ft_strlen(*s) + 1)
			* sizeof(char));
	ft_strcat(*value, *s);
	if (*s)
		free(*s);
	return (err);
}

t_token	*lexer_collect_word(t_lexer *lexer)
{	
	char	*value;
	char	*s;
	int		err;
	int		is_id;

	value = malloc(1 * sizeof(char));
	value[0] = '\0';
	is_id = 0;
	while (is_word(lexer->c))
	{
		err = lexer_collect_word_main(lexer, &s, &value, &is_id);
		if (err)
		{
			free(value);
			return (init_token(TOKEN_ERR, ft_strdup("Quotes not closed")));
		}
		if (*value == '\0' && is_id)
		{
			free(value);
			value = NULL;
		}
	}
	return (init_token(TOKEN_WORD, value));
}
