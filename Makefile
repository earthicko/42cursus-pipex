NAME			= pipex
BONUS			= 

LIBFT_DIR		= libft
LIBFT			= libft.a
LINK_LIBFT		= -L $(LIBFT_DIR) $(LIBFT_DIR)/$(LIBFT)
INC_DIR_LIBFT	= -I $(LIBFT_DIR)

INC_DIR			= -I . $(INC_DIR_LIBFT) -I includes

SRCDIR			= ./src
SRCNAME			= \
				$(SRCDIR)/pipex \
				$(SRCDIR)/utils/str_utils \
				$(SRCDIR)/parser/parser

SRCNAME_BONUS	= \

SRC				= $(addsuffix .c, $(SRCNAME))
OBJ				= $(addsuffix .o, $(SRCNAME))
SRC_BONUS		= $(addsuffix .c, $(SRCNAME_BONUS)))
OBJ_BONUS		= $(addsuffix .o, $(SRCNAME_BONUS))

RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(INC_DIR) $(OBJ) $(LINK_LIBFT) -o $(NAME)

bonus : $(LIBFT) $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(INC_DIR) $(OBJ_BONUS) $(LINK_LIBFT) -o $(BONUS)

$(LIBFT) :
	make -C $(LIBFT_DIR)/

%.o : %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean :
	$(RM) $(OBJ) $(OBJ_BONUS) $(NAME).o $(BONUS).o
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME) $(BONUS)
	make fclean -C $(LIBFT_DIR)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re $(NAME) bonus
