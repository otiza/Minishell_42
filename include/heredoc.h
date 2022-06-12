/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:51:13 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 19:16:48 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H

# define HEREDOC_H
# include "as.h"
# include "token.h"
# include "minishell.h"
# include "lexer.h"

void	input_heredoc(t_as *root);
t_token	*lexer_collect_hered(t_lexer *lexer);
void	replace_input(char **input, t_as *root);
char	*parser_input_exit_status(char *new, int *i);
char	*copy_env(char **env, char **new, char **envp, int *i);
char	*replace_env_input(char *input, char *new, t_vector *v, char **envp);
void	replace_file_name_loop(char **s, char **new,
			t_vector v, int *is_quoted);
int		replace_file_name(char **s);
void	collect_inputs_readl(char *delim, int is_quoted, int fd, t_as *root);
char	*index_file(int index);
int		collect_inputs(t_redirect *redi, int is_quoted, t_as *root, int i);
void	input_heredoc(t_as *root);

#endif