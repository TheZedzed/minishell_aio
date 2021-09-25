# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 11:57:47 by azeraoul          #+#    #+#              #
#    Updated: 2021/08/20 00:09:27 by azeraoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	libft.a
CC		:=	gcc
CPPFLAGS	:= -I./include
CFLAGS	:=	-Wall -Wextra -Werror
SRCS 	:=	$(addsuffix .c, bsd/ft_strlcpy bsd/ft_strlcat \
			stdlib/ft_atoi stdlib/ft_calloc \
			string/ft_strdup string/ft_strndup \
			string/ft_strlen string/ft_strcat string/ft_strncat \
			string/ft_strchr string/ft_strnstr string/ft_memchr \
			string/ft_strncmp string/ft_strcmp string/ft_memcmp \
			string/ft_memset string/ft_bzero string/ft_memcpy string/ft_memmove \
			write/ft_putchar_fd write/ft_putstr_fd write/ft_putnbr_fd \
			ctype/ft_isalpha ctype/ft_isdigit ctype/ft_isspace ctype/ft_isalnum \
			ctype/ft_isascii ctype/ft_isprint ctype/ft_toupper ctype/ft_tolower \
			list/ft_lstadd_back list/ft_lstadd_front list/ft_lstclear \
			list/ft_lstdelone list/ft_lstlast list/ft_lstnew list/ft_lstsize \
			btree/ft_apply_level btree/ft_level_count btree/ft_create_node \
			btree/ft_apply_suffix btree/ft_apply_infix btree/ft_apply_prefix \
			utils/get_next_line utils/ft_itoa utils/ft_split utils/ft_strjoin \
			utils/ft_strtrim utils/ft_substr utils/ft_atoi_base)
OBJS 	:=	$(SRCS:.c=.o)
RM		:=	rm -f
AR		:=	ar -rcs

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS)

%.o: %.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
