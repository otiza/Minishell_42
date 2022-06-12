/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:24:50 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/15 04:34:36 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	siginit(void)
{
	signal(SIGINT, sighandle);
	signal(SIGQUIT, sighandle);
}

void	handlesigquit(void)
{
	if (g_main.isfork == 1)
	{
		g_main.exit_stat = 131;
		write(1, "Quit: 3\n", 9);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
	{
		rl_on_new_line ();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 1);
	}
}

void	sighandle(int sig)
{
	if (sig == SIGQUIT)
	{
		handlesigquit();
	}
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_putstr_fd("  \b\b", 1);
		if (g_main.isfork == 0)
		{
			rl_redisplay();
			ft_putchar_fd('\n', 1);
			ft_putstr_fd("Minishell >", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		g_main.exit_stat = 130;
	}
}

void	deleteargs(int argc, char **argv)
{
	(void)argc;
	**argv = 0;
}

int	thisisfornorme(char **str)
{
	siginit();
	if (my_readline(str) == 1)
		return (1);
	return (0);
}
