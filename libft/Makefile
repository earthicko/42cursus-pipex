NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCNAME		= \
			ft_isalpha \
			ft_isdigit \
			ft_isalnum \
			ft_isascii \
			ft_isprint \
			ft_isspace \
			ft_strlen \
			ft_memset \
			ft_bzero \
			ft_memcpy \
			ft_memmove \
			ft_strlcpy \
			ft_strlcat \
			ft_toupper \
			ft_tolower \
			ft_strchr \
			ft_strrchr \
			ft_strncmp \
			ft_memchr \
			ft_memcmp \
			ft_strnstr \
			ft_atoi \
			ft_calloc \
			ft_strdup \
			ft_substr \
			ft_strjoin \
			ft_strtrim \
			ft_split \
			ft_itoa \
			ft_strmapi \
			ft_striteri \
			ft_putchar_fd \
			ft_putstr_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_lstnew \
			ft_lstadd_front \
			ft_lstsize \
			ft_lstlast \
			ft_lstadd_back \
			ft_lstdelone \
			ft_lstclear \
			ft_lstiter \
			ft_lstmap \
			get_next_line \
			get_next_line_utils \
			get_next_line_utils2 \
			ft_printf \
			t_conv \
			ft_str_utils \
			ft_numlen \
			parse_format \
			parse_format_utils \
			create_str \
			create_str_utils \
			fwrite_chr \
			fwrite_num \
			fwrite_ptr \
			fwrite_utils

SRC			= $(addsuffix .c, $(SRCNAME))
OBJ			= $(addsuffix .o, $(SRCNAME))

all: ${NAME}

objs :
	make -j 4 $(OBJ)

${NAME} : objs
	ar -rcus ${NAME} ${OBJ}

.c.o :
	${CC} ${CFLAGS} -c $< -o $@

clean :
	${RM} ${OBJ}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all bonus clean fclean re $(NAME)
