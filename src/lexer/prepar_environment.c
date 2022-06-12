/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepar_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:11:58 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/15 01:13:43 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

char	*ft_get_environment(char **envp, char *argv)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (is_var(envp[i], argv))
			return (envp[i] + ft_strlen(argv) + 1);
		i++;
	}
	return (NULL);
}

char	*copy_environment(char **environment, char **new, char **envp, int *i)
{
	char	*tmp;

	tmp = *environment;
	*environment = ft_get_environment(envp, tmp);
	free(tmp);
	if (!(*environment))
		return (*new);
	*i += ft_strlen(*environment);
	tmp = ft_strjoin(*new, *environment);
	free(*new);
	return (tmp);
}

char	*replace_environment(t_lexer *lexer, char *new, int *i)
{
	char	*environment;
	char	*tmp;
	int		count_environment;

	count_environment = 0;
	lexer_advance(lexer);
	if (lexer->c == '?')
		return (parser_parse_exit_status(lexer, new, i));
	environment = malloc(1 * sizeof(char));
	while ((ft_isalnum(lexer->c) || lexer->c == '_') && lexer->c)
	{
		environment[count_environment++] = lexer->c;
		environment = ft_realloc(environment,
				sizeof(char) * count_environment + 1);
		lexer_advance(lexer);
	}
	if (count_environment == 0)
	{
		return (replace_fss(&i, &environment, &tmp, &new));
	}
	environment[count_environment] = '\0';
	return (copy_environment(&environment, &new, lexer->envp, i));
}

char	*replace_fss(int **i, char **environment, char **tmp, char **new)

{
	**i += 1;
	free(*environment);
	*tmp = ft_strjoin(*new, "$");
	free(*new);
	return (*tmp);
}
