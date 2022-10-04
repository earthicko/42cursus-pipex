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
				$(SRCDIR)/datatypes/procinfo \
				$(SRCDIR)/datatypes/execinfo \
				$(SRCDIR)/before_fork/procinfo_constructor \
				$(SRCDIR)/before_fork/path_finder \
				$(SRCDIR)/before_fork/pipe_creator \
				$(SRCDIR)/after_fork/forker \
				$(SRCDIR)/after_fork/io_fd_setter \
				$(SRCDIR)/after_fork/arg_parser \
				$(SRCDIR)/after_fork/ft_split_escape

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
