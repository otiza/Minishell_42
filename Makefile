# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/22 15:21:58 by zsidki            #+#    #+#              #
#    Updated: 2022/02/15 04:28:43 by amaaiza          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all fclean clean re
CC = gcc
flags =   -Wall -Wextra -Werror -g -fsanitize=address
SRCS =  src/token.c src/as.c minishell.c src/exec/pipe.c src/exec/builtin.c src/env/env.c src/exec/nonbuiltin.c src/exec/builtin_tools.c src/exec/redirec.c\
		src/parser/parser.c src/parser/free_parser_as.c src/parser/parser_parse.c \
		src/lexer/prepar_environment.c src/lexer/collect_word.c src/lexer/lexer.c \
		src/lexer/collect_quote_redi_id.c src/lexer/utils.c src/heredoc/heredoc.c src/heredoc/heredoc_pr.c src/heredoc/heredoc_utils.c\
		src/env/env_list_tools.c src/env/env_list_tools2.c src/exec/sig.c  src/exec/builtin_tools2.c src/exec/builtin_help.c src/env/env_list.c\
		

NAME  = minishell

all : $(NAME)

$(NAME): ${SRCS}
	make -C libft/ all
	@$(CC) $(flags) $(SRCS) libft/libft.a -o $(NAME) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include/

clean:
	make -C libft/ fclean
	@rm -rf $(NAME)

fclean: clean

re: fclean all

push:
	@git add .
	@git commit -m "$(m)"
	@git push -f origin master
