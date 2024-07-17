# List of source files
FILES       =   free.c \
                getters_utils.c \
                main.c \
                parameters_editors.c \
                solvers.c \
                string_checkers.c \
                string_editors.c\
				errors_handlers.c\
				write_functions.c\
				extra_utils.c

# Sources and objects
SRC         =   $(FILES)

OBJS_SRC    =   $(SRC:.c=.o)

OBJS        =   $(OBJS_SRC)

# Compiler and flags
GCC         =   gcc -g3
FLAGS       =   -Wall -Wextra -Werror
INCLUDE     =   -I include

# Output name
NAME        =   computorv1

# Build target
all: $(NAME)

# Link the executable
$(NAME): $(OBJS)
	$(GCC) $(FLAGS) $(OBJS) -o $(NAME) -lm

# Clean object files
clean:
	@rm -rf $(OBJS)

# Clean object files and the executable
fclean: clean
	@rm -rf $(NAME)

# Compile source files to object files
%.o: %.c
	$(GCC) $(FLAGS) $(INCLUDE) -c $< -o $@

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re
