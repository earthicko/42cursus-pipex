NAME			= pipex

LIBFT_DIR		= libft
LIBFT			= libft.a
LINK_LIBFT		= -L $(LIBFT_DIR) $(LIBFT_DIR)/$(LIBFT)
INC_DIR_LIBFT	= -I $(LIBFT_DIR)

INC_DIR			= -I . $(INC_DIR_LIBFT) -I includes

SRCDIR			= ./src
SRCNAME			= \
				$(SRCDIR)/pipex \
				$(SRCDIR)/datatypes/intarr \
				$(SRCDIR)/datatypes/strarr \
				$(SRCDIR)/datatypes/execinfo \
				$(SRCDIR)/executor/forker \
				$(SRCDIR)/parser/execinfo_constructor \
				$(SRCDIR)/parser/path_finder \
				$(SRCDIR)/parser/pipe_creator

SRC				= $(addsuffix .c, $(SRCNAME))
OBJ				= $(addsuffix .o, $(SRCNAME))

RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(INC_DIR) $(OBJ) $(LINK_LIBFT) -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)/

%.o : %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean :
	$(RM) $(OBJ) $(NAME).o
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re $(NAME)
