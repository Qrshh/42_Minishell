NAME	=	libft.a

CC				= gcc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror

SRCS    		=		ft_is/ft_isalnum.c \
					ft_is/ft_isalpha.c \
					ft_is/ft_isascii.c \
					ft_is/ft_isdigit.c \
					ft_is/ft_isprint.c \
					ft_put/ft_putchar_fd.c \
					ft_put/ft_putendl_fd.c \
					ft_put/ft_putstr_fd.c \
					ft_str/ft_strchr.c \
					ft_str/ft_strlen.c \
					ft_to/ft_tolower.c \
					ft_to/ft_toupper.c \
					ft_str/ft_strrchr.c \
					ft_mem/ft_memset.c \
					ft_mem/ft_memcpy.c \
					ft_mem/ft_bzero.c \
					ft_mem/ft_memmove.c \
					ft_str/ft_strncmp.c \
					ft_str/ft_strlcpy.c \
					ft_mem/ft_memchr.c \
					ft_str/ft_strlcat.c \
					ft_mem/ft_memcmp.c \
					ft_str/ft_strstr.c \
					ft_str/ft_strnstr.c \
					ft_to/ft_atoi.c \
					ft_str/ft_strdup.c \
					ft_mem/ft_calloc.c \
					ft_str/ft_substr.c \
					ft_str/ft_strjoin.c \
					ft_str/ft_split.c \
					ft_to/ft_itoa.c \
					ft_str/ft_strtrim.c \
					ft_put/ft_putnbr_fd.c \
					ft_str/ft_strmapi.c \
					ft_str/ft_striteri.c \
					ft_str/ft_strndup.c \
					ft_str/ft_strcmp.c \
					ft_str/ft_strcat.c \
					ft_str/ft_strcpy.c \
					ft_str/ft_strncpy.c \
					ft_gnl/get_next_line.c \
					ft_gnl/get_next_line_utils.c \
					ft_printf/ft_printf_utils.c \
					ft_printf/ft_printf.c
					

					
OBJS			=	$(SRCS:.c=.o)

BONUS			=		ft_lst/ft_lstnew.c \
					ft_lst/ft_lstadd_front.c \
					ft_lst/ft_lstsize.c \
					ft_lst/ft_lstlast.c \
					ft_lst/ft_lstadd_back.c \
					ft_lst/ft_lstdelone.c \
					ft_lst/ft_lstclear.c \
					ft_lst/ft_lstiter.c \
					ft_lst/ft_lstmap.c \

BONUS_OBJS		= 	$(BONUS:.c=.o)


all: ${NAME}

${NAME}:		${OBJS} $(BONUS_OBJS)
				ar rcs $(NAME) ${OBJS}
clean:
				$(RM) $(OBJS) $(BONUS_OBJS)
fclean:			clean
				$(RM) $(NAME)	
bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
re: fclean ${NAME}

.PHONY: all, clean, fclean, re	

.SILENT:
