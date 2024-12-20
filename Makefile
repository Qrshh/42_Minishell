# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 09:05:48 by abesneux          #+#    #+#              #
#    Updated: 2024/11/18 16:19:53 by ozdemir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
INCLUDES    = includes/
SRC_DIR     = src/
OBJ_DIR     = obj/

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -I/opt/homebrew/opt/readline/include
LDFLAGS		= -L/opt/homebrew/opt/readline/lib -lreadline
RM          = rm -rf

GREEN		=	\e[92;5;118m
YELLOW		= 	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET 		=	\e[0m
CURSIVE		=	\e[33;3m

LIBFT_DIR    = $(INCLUDES)Libft/
LIBFT        = $(LIBFT_DIR)libft.a
LIBFT_CFLAGS = -fPIC

PARSING_DIR = parsing/
PARSING 	= syntax_checker syntax_checker_utils handle_dollar handle_operator heredoc

LEXING_DIR = lexing/
LEXING     = handle_token lexer tokenize handle_token_utils

BUILTINS_DIR = builtins/
BUILTINS = handle_builtins echo exit pwd export export_utils env unset cd

EXECUTING_DIR = executing/
EXECUTING = execute execute_utils execute_utils2 execute_utils3

UTILS_DIR = utils/
UTILS     = utils1 utils2

SRC_FILES  += minishell utils signal free arena
SRC_FILES += $(addprefix $(BUILTINS_DIR), $(BUILTINS))
SRC_FILES += $(addprefix $(LEXING_DIR), $(LEXING))
SRC_FILES += $(addprefix $(PARSING_DIR), $(PARSING))
SRC_FILES += $(addprefix $(EXECUTING_DIR), $(EXECUTING))
SRC_FILES += $(addprefix $(UTILS_DIR), $(UTILS))

SRC         = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJ_CACHE   = .cache_exists

all: 			 $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) CFLAGS+=$(LIBFT_CFLAGS)

$(NAME): 		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)
					@printf "$(GREEN)	- Executable ready.\n$(RESET)"
					
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_CACHE)
					@printf "$(GRAY)Compiling $<\n$(RESET)"
					@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJ_CACHE):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)
					@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
					@mkdir -p $(OBJ_DIR)$(LEXING_DIR)
					@mkdir -p $(OBJ_DIR)$(EXECUTING_DIR)
					@mkdir -p $(OBJ_DIR)$(UTILS_DIR)

clean:
					@make clean -C $(LIBFT_DIR)
					$(RM) $(OBJ_DIR)
					$(RM) $(OBJ_CACHE)
					@printf "$(YELLOW)Object files cleaned\$(RESET)"

fclean: 		clean
					@make fclean -C $(LIBFT_DIR)
					$(RM) $(NAME) $(BONUS_NAME)
					@printf "$(YELLOW)Object files and executabe removed\n$(RESET)"

re: 			fclean all

.PHONY:			all clean fclean re bonus

.SILENT:
