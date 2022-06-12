/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:19:41 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 22:46:06 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "lexer.h"
# include "token.h"
# include "as.h"
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_main
{
	int		exit_stat;
	int		inheredoc;
	int		isfork;
	int		sigint;

}	t_main;

typedef struct s_vector
{
	int	i;
	int	j;

}	t_vector;

t_main	g_main;

void	parse(char *cmd, char **envp, t_env *env, t_as *as);

#endif
