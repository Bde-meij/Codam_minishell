# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbrune <rbrune@student.42.fr>                +#+                      #
#                                                    +#+                       #
#    Created: 2022/05/30 12:40:51 by rbrune        #+#    #+#                  #
#    Updated: 2023/01/16 15:43:34 by rbrune        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc 
CFLAGS  = -Werror -Wall -Wextra

# exe name
NAME = minishell

# C Files
SRC = main.c  \
filemanagement/in_out_files.c \
filemanagement/heredocs.c \
builtins/builtins.c \
builtins/echo.c builtins/envp_functions.c builtins/unset.c \
builtins/cd.c builtins/export.c \
 tokenize/tokenizers.c \
tokenize/enlist_tokens.c \
 execution/search_env.c execution/cmd_exe.c \
execution/search_command.c execution/execute_cmds.c\
other/main_utils.c other/protect_n_free.c other/signals.c \
other/error_messages.c expansion/expand.c expansion/expand_utils.c \
expansion/expand_empty_var.c expansion/expand_exit_code.c \
tokenize/tokenize_input.c \
other/free_token_reset_fd.c

# Object files
OBJ = $(SRC:.c=.o)

#Library
LIBFT_LOC	= ./libft
LIBFT		= ./libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	$(MAKE) -s -C $(LIBFT_LOC)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	

clean:
	$(MAKE) -s -C $(LIBFT_LOC) clean
	rm -f $(OBJ)

fclean:
	$(MAKE) -s -C $(LIBFT_LOC) fclean
	rm -f $(NAME) $(OBJ) 

re: fclean
	$(MAKE) all

.PHONY: clean fclean all re