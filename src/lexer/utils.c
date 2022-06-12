/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 23:37:26 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 18:46:26 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	is_var(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] - s2[i] == 0 && s1[i] != '\0' && s2[i] != '\0')
	{
		if ((s1[i] == '=' && s2[i] == '=') || ft_strcmp(s1, s2) == 0)
			return (1);
		i++;
	}
	if ((s1[i] == '=' && s2[i] == '\0')
		|| (s1[i] == '\0' && s2[i] == '='))
		return (1);
	return (0);
}

char	*parser_parse_exit_status(t_lexer *lexer, char *new, int *i)
{
	char	*exit_status;	
	char	*tmp;

	exit_status = ft_itoa(g_main.exit_stat);
	*i += ft_strlen(exit_status);
	tmp = ft_strjoin(new, exit_status);
	if (exit_status)
		free(exit_status);
	free(new);
	lexer_advance(lexer);
	return (tmp);
}
