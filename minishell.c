/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:19:30 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/15 04:27:28 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/parser.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	parse(char *cmd, char **envp, t_env *env, t_as *as)
{
	t_lexer		*lexer;
	t_parser	*parser;

	lexer = init_lexer(cmd);
	lexer->envp = envp;
	parser = init_parser(lexer);
	parser_parse(parser, as);
	get_redi(as);
	as->env = env;
	free_parser(parser);
}

int	my_readline(char **str)
{
	*str = readline("Minishell >");
	if (!(*str))
	{
		return (1);
	}
	return (0);
}

void	ft_paarse(char *str, char **envp, t_env *env, t_as *as)
{
	add_history(str);
	parse(str, envp, env, as);
}

void	cmdstart(t_as *as)
{
	if (as->cmds_size == 1 && as->cmds[0])
	{
		ft_check(as, as->cmds[0]);
	}
	if (as->cmds_size < 557 && as->cmds_size > 1 && as->cmds)
	{
		pipes(as);
	}
	g_main.exit_stat = as->exitstat;
	g_main.sigint = as->sigint;
}

int	main(int argc, char **argv, char **envp)
{
	t_as	*as;
	char	*str;
	t_env	*env;

	env = ft_addevnlist(&env, envp, &envp, &as);
	argeror(argc, argv);
	while (1)
	{
		if (thisisfornorme(&str) == 1)
			return (0);
		if (str[0] != '\0')
		{
			ft_paarse(str, envp, env, as);
			if (as->cmds)
			{
				cmdstart(as);
				free(str);
				if (as == NULL)
					continue ;
				envpcast(&envp, as->env);
			}
			free_as(as);
		}
	}
	return (0);
}
