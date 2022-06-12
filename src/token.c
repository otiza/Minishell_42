/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:29:55 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 18:29:59 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/token.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = malloc(1 * sizeof(struct s_token));
	token->e_type = type;
	token->value = value;
	return (token);
}
