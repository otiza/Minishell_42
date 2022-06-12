/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:57:05 by zsidki            #+#    #+#             */
/*   Updated: 2022/02/14 19:33:50 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_token
{
	enum
	{
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_LESS,
		TOKEN_GREAT,
		TOKEN_MLESS,
		TOKEN_MGREAT,
		TOKEN_ERR,
		TOKEN_EOF
	}	e_type;
	char	*value;
}				t_token;

t_token	*init_token(int type, char *value);

#endif
