/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:09:42 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 19:18:19 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"
#include "../../include/heredoc.h"

char	*parser_input_exit_status(char *new, int *i)
{
	char	*exit_status;
	char	*tmp;

	exit_status = ft_itoa(g_main.exit_stat);
	*i += ft_strlen(exit_status);
	tmp = ft_strjoin(new, exit_status);
	if (exit_status)
		free(exit_status);
	free(new);
	return (tmp);
}

char	*copy_env(char **env, char **new, char **envp, int *i)
{
	char	*tmp;

	tmp = *env;
	*env = ft_get_environment(envp, tmp);
	free(tmp);
	if (!(*env))
		return (*new);
	*i += ft_strlen(*env);
	tmp = ft_strjoin(*new, *env);
	free(*new);
	return (tmp);
}

char	*replace_env_input(char *input, char *new, t_vector *v, char **envp)
{
	char	*env;
	char	*tmp;
	int		count_env;

	count_env = 0;
	if (input[++v->j] == '?')
	{
		v->j += 1;
		return (parser_input_exit_status(new, &(v->i)));
	}
	env = malloc(1 * sizeof(char));
	while ((ft_isalnum(input[v->j]) || input[v->j] == '_') && input[v->j])
	{
		env[count_env++] = input[v->j++];
		env = ft_realloc(env, sizeof(char) * count_env + 1);
	}
	if (count_env == 0)
	{
		v->i += 1;
		free(env);
		tmp = ft_strjoin(new, "$");
		free(new);
		return (tmp);
	}
	return (copy_env(&env, &new, envp, &(v->i)));
}

void	replace_input(char **input, t_as *root)
{
	char		*new;
	t_vector	v;

	new = malloc(1 * sizeof(char));
	*new = 0;
	v.i = 0;
	v.j = 0;
	while ((*input)[v.j])
	{
		if ((*input)[v.j] == '$')
			new = replace_env_input(*input, new, &v, root->envp);
		else
		{
			new = ft_realloc(new, sizeof(char) * v.i + 2);
			new[v.i++] = (*input)[v.j];
			v.j++;
		}
	}
	new[v.i] = '\0';
	free(*input);
	*input = ft_strdup(new);
	free(new);
}

void	replace_file_name_loop(char **s, char **new,
			t_vector v, int *is_quoted)
{
	char	curr_quoted;

	curr_quoted = 0;
	while ((*s)[v.i] != '\0')
	{
		if (((*s)[v.i] != '\'' && (*s)[v.i] != '\"')
			|| (curr_quoted != (*s)[v.i] && curr_quoted))
		{
			*new = ft_realloc(*new, sizeof(char) * v.j + 2);
			(*new)[v.j++] = (*s)[v.i];
		}
		else if ((*s)[v.i] == curr_quoted)
			curr_quoted = 0;
		else
		{
			curr_quoted = (*s)[v.i];
			*is_quoted = 1;
		}
		v.i++;
	}
	(*new)[v.j] = '\0';
}
