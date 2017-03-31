# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opodolia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/20 16:00:27 by opodolia          #+#    #+#              #
#    Updated: 2017/03/31 14:34:20 by opodolia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
NAME_BASE = ft_ls

# compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# directories
LS_SRC_DIR = ./src/
LS_OBJ_DIR = ./obj/
LS_INC_DIR = ./includes/

# fdf source files
LS_FILES = main.c file.c sort.c length.c  row_col.c print.c print_items.c \
		   print_files.c

LS_OBJ = $(addprefix $(LS_OBJ_DIR), $(LS_FILES:.c=.o))

# libftprintf
LIB_DIR = ./libft_printf/
LIB = $(addprefix $(LIB_DIR), libftprintf.a)
LIB_INC = -I ./libft_printf
LIB_LNK = -L ./libft_printf -l ftprintf

.SILENT:

all: $(LIB) $(NAME)
	echo "\033[38;5;44m☑️  ALL    $(NAME_BASE) is done\033[0m\033[K"

$(LS_OBJ_DIR)%.o: $(LS_SRC_DIR)%.c
	printf "\r\033[38;5;11m⌛  MAKE $(NAME_BASE) please wait ...\033[0m\033[K"
	mkdir -p $(LS_OBJ_DIR)
	$(CC) $(CFLAGS) $(LIB_INC) -I $(LS_INC_DIR) -o $@ -c $<

$(LIB):
	make -C $(LIB_DIR)

$(NAME): $(LS_OBJ)
	$(CC) $(LS_OBJ) $(LIB_LNK) -lm -o $(NAME)
	echo -en "\r\033[38;5;22m☑️  MAKE $(NAME_BASE)\033[0m\033[K"
	echo "\r\033[38;5;184m👥  GROUP MEMBER(S):\033[0m\033[K"
	echo "\r\033[38;5;15m`cat author | sed s/^/\ \ \ \ /g`\033[0m\033[K 🇺🇦"

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_BASE) please wait ...\033[0m\033[K"
	rm -rf $(LS_OBJ_DIR)
	make -C $(LIB_DIR) clean
	printf "\r\033[38;5;11m☑️  CLEAN  $(NAME_BASE) is done\033[0m\033[K"

fclean: clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_BASE) please wait ...\033[0m\033[K"
	rm -f $(NAME)
	make -C $(LIB_DIR) fclean
	printf "\r\033[38;5;11m☑️  FCLEAN  $(NAME_BASE) is done\033[0m\033[K"

re: fclean all

.PHONY: fclean clean re
