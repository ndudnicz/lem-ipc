NAME = lemipc
CC = gcc
CFLAGS = #-Werror -Wextra -Wall #-std=c89 -Werror -Wextra -Wall
DEBUGFLAGS = #-fsanitize=address -g3

# SOURCE FOLDERS ==============================================================#

SRC_DIR = src

# OBJECTS FOLDERS =============================================================#

OBJ_DIR = obj

# INCLUDES FOLDERS ============================================================#

PATH_INCLUDES = includes
PATH_INCLUDES_LIBFT = libft/includes

# SOURCES LIST ================================================================#

SRC = \
main.c \
error.c \
init_ipcs.c \
clean_ipcs.c \
check_sides.c \
play.c \
print.c \
signal_handler.c \
player.c \
debug.c \
clean_board.c \
msg.c \
moves.c \
turn.c \
select_move.c \
can_move.c \
win.c \
release_sem.c \

# OBJECTS LIST ================================================================#

OBJ = $(SRC:%.c=obj/%.o)
DEP = $(SRC:%.c=obj/%.d)

# GENERIC RULES ===============================================================#

all: $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJ) $(DEP)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: clean fclean all

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ) -L. -lft -L. -lftasm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -MMD -o $@ -c $< -I $(PATH_INCLUDES) -I $(PATH_INCLUDES_LIBFT)

-include $(OBJ:.o=.d)
