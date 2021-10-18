# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/19 11:42:25 by azeraoul          #+#    #+#              #
#    Updated: 2021/10/06 18:32:14 by azeraoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-fsanitize=address -fsanitize=leak -fno-omit-frame-pointer
#-fsanitize=memory -fPIE -pie
NAME	:= minishell
CC		:= gcc 
CFLAGS	:= -g -Werror -Wextra -Wall
CPPFLAGS = -I./libft/include -I./includes
LDFLAGS	:= -L./libft -L./usr/lib/x86_64-linux-gnu
LDLIBS	:= -lft -lreadline
FILES	:=	main lexer/lexer parser/parser \
			lexer/lexer_err/lexer_err lexer/lexer_err/syntax_err lexer/lexer_err/syntaxb_err \
			lexer/debug/debug lexer/debug/free lexer/debug/show_ast \
			lexer/utils/tokenizer lexer/utils/lexer_utils lexer/utils/token_utils \
			parser/ast/ast parser/ast/ast2 \
			parser/builtin/blt parser/builtin/e_blt parser/builtin/cd_blt \
			parser/cmd/parse_cmd parser/cmd/expand parser/cmd/redir parser/cmd/cmd parser/cmd/stars \
			parser/exec/executer parser/exec/pipex parser/exec/exec_cmd \
			parser/env/env parser/env/search parser/env/assign \
			parser/utils/parser_utils
RM		:= rm -rf
SRCS := $(addsuffix .c, $(addprefix srcs/, $(FILES)))
SRCS_B := $(addsuffix _bonus.c, $(addprefix srcs_bonus/, $(FILES)))
OBJS := $(SRCS:.c=.o)
OBJS_B := $(SRCS_B:.c=.o)

ifeq ($(BONUS), 1)
	CPPFLAGS = -I./libft/include -I./includes_bonus
	SRCS = $(SRCS_B)
	OBJS = $(OBJS_B)
endif

.Phony: all re clean fclean bonus

all: $(NAME)

bonus:
	make BONUS=1

$(NAME): $(OBJS)
	make --silent -C ./libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	make clean --silent -C ./libft
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	make fclean --silent -C ./libft
	$(RM) $(NAME)

re: fclean all
