/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:55:37 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/15 01:01:18 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "token.h"
# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char			*contents;
	char			**envp;
}					t_lexer;

t_lexer		*init_lexer(char *contents);
void		lexer_advance(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
t_token		*lexer_get_next_token(t_lexer *lexer);
t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token);
char		*ft_get_environment(char **envp, char *argv);
char		*copy_environment(char **environment,
				char **new, char **envp, int *i);
char		*replace_environment(t_lexer *lexer, char *new, int *i);
char		*lexer_collect_single_quote(t_lexer *lexer, int *err);
char		*lexer_collect_double_quote(t_lexer *lexer, int *err);
t_token		*lexer_collect_redirection(t_lexer *lexer, int *is_heredoc);
char		*lexer_collect_id(t_lexer *lexer);
int			lexer_collect_word_main(t_lexer *lexer, char **s,
				char **value, int *is_id);
t_token		*lexer_collect_word(t_lexer *lexer);
int			is_var(char *s1, char *s2);
int			is_word(char c);
int			is_id(char c);
char		*parser_parse_exit_status(t_lexer *lexer, char *new, int *i);
char		*replace_fss(int **i, char **environment, char **tmp,
				char **new);
#endif
