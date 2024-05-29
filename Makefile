# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 09:05:48 by abesneux          #+#    #+#              #
#    Updated: 2024/05/29 16:30:11 by abesneux         ###   ########.fr        #
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
					@echo "\033[0;32m$(shell echo $(NAME) | tr '[:lower:]' '[:upper:]') : COMPILED\033[0m"
					
$(BONUS_NAME):	$(OBJ)
					$(CC) $(CFLAGS) $(SRC_DIR)$(BONUS_SRC) $(filter-out $(SRC_DIR)main.c, $(SRC)) $(LIBFT) -o $(BONUS_NAME)
					@echo "\033[0;32m$(shell echo $(BONUS_NAME) | tr '[:lower:]' '[:upper:]') : COMPILED\033[0m"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_CACHE)
					@echo "Compiling $<"
					@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJ_CACHE):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)

clean:
					@make clean -C $(LIBFT_DIR)
					$(RM) $(OBJ_DIR)
					$(RM) $(OBJ_CACHE)
					@echo "minsihell and libs object files cleaned!"

fclean: 		clean
					@make fclean -C $(LIBFT_DIR)
					$(RM) $(NAME) $(BONUS_NAME)
					@echo "minishell and libs executable files cleaned!"

re: 			fclean all
					@echo "Cleaned and rebuilt everything for minishell!"


.PHONY:			all clean fclean re bonus

.SILENT: