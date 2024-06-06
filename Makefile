# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qrshh <qrshh@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 09:05:48 by abesneux          #+#    #+#              #
#    Updated: 2024/06/03 20:32:27 by qrshh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
INCLUDES    = includes/
SRC_DIR     = src/
OBJ_DIR     = obj/

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
LDFLAGS		= -lreadline
RM          = rm -rf

GREEN		=	\e[92;5;118m
YELLOW		= 	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET 		=	\e[0m
CURSIVE		=	\e[33;3m

LIBFT_DIR    = $(INCLUDES)Libft/
LIBFT        = $(LIBFT_DIR)libft.a
LIBFT_CFLAGS = -fPIC


BUILTINS_DIR = builtins/
BUILTINS = pwd

SRC_FILES  += minishell utils_all execute
SRC_FILES += $(addprefix $(BUILTINS_DIR), $(BUILTINS))

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

clean:
					@make clean -C $(LIBFT_DIR)
					$(RM) $(OBJ_DIR)
					$(RM) $(OBJ_CACHE)
					@printf "$(YELLOW)minsihell and libs object files cleaned!\n$(RESET)"

fclean: 		clean
					@make fclean -C $(LIBFT_DIR)
					$(RM) $(NAME) $(BONUS_NAME)
					@printf "$(YELLOW)minishell and libs executable files cleaned!\n$(RESET)"

re: 			fclean all


.PHONY:			all clean fclean re bonus

.SILENT: