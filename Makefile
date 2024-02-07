CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f
NAME = minishell

LIBFT_DIR = libraries/libft
LIBFT = libft.a
EXECUTOR_DIR = executor/
BUILTIN_DIR = builtin/

# define the C source files
SRCS = 	$(EXECUTOR_DIR)main.c	\
		$(EXECUTOR_DIR)executor.c	\
		$(EXECUTOR_DIR)other_utils.c	\
		$(EXECUTOR_DIR)env_utils.c	\
		$(BUILTIN_DIR)echo.c

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
# For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS with the .o suffix
OBJS = $(SRCS:.c=.o)

# -c option tells the compiler to generate an object file without linking
%.o: %.c executor.h
	$(CC) $(CFLAGS) -c -g $< -o $@

all: $(NAME)

# -C DIRECTORY
# Change to DIRECTORY before doing anything.
$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all 

.PHONY: all clean fclean re
