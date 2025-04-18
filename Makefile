NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# Detect system and set appropriate readline flags
UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)

ifeq ($(UNAME_S),Darwin)
  ifeq ($(UNAME_P),arm)
    # macOS on ARM (Apple Silicon)
    READLINE_INC = -I$(shell brew --prefix readline)/include
    READLINE_LIB = -L$(shell brew --prefix readline)/lib
    RL_FLAGS = $(READLINE_LIB) -lreadline $(READLINE_INC)
  else
    # macOS on Intel
    RL_FLAGS = -lreadline
  endif
else
  # Linux and other systems
  RL_FLAGS = -lreadline
endif

# Directories
BUILTIN_DIR	= builtin
UTILS_DIR	= utils
PARSING_DIR	= parsing
EXEC_DIR	= executing
OBJ_DIR		= .obj

# Header files
HEADERS		= minishell.h

# Source files
BUILTIN_SRC	= env_functions.c env_parsing.c ft_cd.c ft_echo.c ft_env.c \
			  ft_export.c ft_pwd.c ft_unset.c ft_exit.c

UTILS_SRC	= char.c char_utils2.c free_functions.c ft_calloc.c \
			  ft_itoa.c strcpy.c

PARSING_SRC	= expand.c expand_null.c expand_var.c init.c split_quote_and_space.c \
			  split_pipe.c add_space.c handle_line.c

EXEC_SRC	= builtin_caller.c executing.c shell_cmd.c get_path.c check_cmd.c \
			  fd_management.c

SRC			= main.c \
			  $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_SRC)) \
			  $(addprefix $(UTILS_DIR)/, $(UTILS_SRC)) \
			  $(addprefix $(PARSING_DIR)/, $(PARSING_SRC)) \
			  $(addprefix $(EXEC_DIR)/, $(EXEC_SRC))

# Object files
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling $(NAME) with readline flags: $(RL_FLAGS)"
	$(CC) $(CFLAGS) $(OBJ) $(RL_FLAGS) -o $(NAME)
	@echo "\033[32mCompilation complete. Executable '$(NAME)' created.\033[0m"

# This pattern rule ensures source files are recompiled if headers or Makefile change
$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[33mObject files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33mExecutable '$(NAME)' removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re