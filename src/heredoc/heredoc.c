/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:27:07 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 19:19:45 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"
#include "../../include/heredoc.h"

int	replace_file_name(char **s)
{
	t_vector	v;
	char		*new;
	int			is_quoted;

	new = malloc(1 * sizeof(char));
	*new = 0;
	v.i = 0;
	v.j = 0;
	is_quoted = 0;
	replace_file_name_loop(s, &new, v, &is_quoted);
	free(*s);
	*s = ft_strdup(new);
	free(new);
	return (is_quoted);
}

void	collect_inputs_readl(char *delim, int is_quoted, int fd, t_as *root)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (g_main.inheredoc == 1)
			break ;
		if (!ft_strcmp(input, delim))
			break ;
		if (!is_quoted)
			replace_input(&input, root);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(input);
}

char	*index_file(int index)
{
	char	*nb;
	char	*file;

	nb = ft_itoa(index);
	file = ft_strjoin("/tmp/", nb);
	free(nb);
	return (file);
}

int	collect_inputs(t_redirect *redi, int is_quoted, t_as *root, int i)
{
	int		fd;
	char	*delim;

	delim = ft_strdup(redi->file);
	free(redi->file);
	redi->file = index_file(i);
	fd = open(redi->file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	collect_inputs_readl(delim, is_quoted, fd, root);
	free(delim);
	return (1);
}

void	input_heredoc(t_as *root)
{
	int	i;
	int	j;
	int	is_quoted;

	i = -1;
	if (root == NULL)
		return ;
	while ((size_t)++i < root->cmds_size)
	{
		j = -1;
		while ((size_t)++j < root->cmds[i]->redi_size)
		{
			if (root->cmds[i]->redi[j]->e_type == HEREDOC)
			{
				is_quoted = replace_file_name(&(root->cmds[i]->redi[j]->file));
				collect_inputs(root->cmds[i]->redi[j], is_quoted, root, i);
			}
		}
	}
}
