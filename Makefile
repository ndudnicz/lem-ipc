NAME = lemipc
CC = gcc
CFLAGS = -std=c89# -Werror -Wextra -Wall
DEBUGFLAGS = -fsanitize=address -g3

# SOURCE FOLDERS ==============================================================#

SRC_DIR = src

# OBJECTS FOLDERS =============================================================#

OBJ_DIR = obj

# INCLUDES FOLDERS ============================================================#

PATH_INCLUDES = includes

# SOURCES LIST ================================================================#

SRC = \
main.c \

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
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -MMD -o $@ -c $< -I $(PATH_INCLUDES)

-include $(OBJ:.o=.d)
