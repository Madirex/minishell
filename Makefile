# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -Wunused -fsanitize=address -I$(INC_DIR) -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib

# Colors for output
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RESET = \033[0m

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
BIN_DIR = bin

# Source subdirectories
AST_DIR = $(SRC_DIR)/ast
BUILTINS_DIR = $(SRC_DIR)/builtins
CORE_DIR = $(SRC_DIR)/core
ENV_DIR = $(SRC_DIR)/env
EXECUTOR_DIR = $(SRC_DIR)/executor
PARSER_DIR = $(SRC_DIR)/parser
SIGNALS_DIR = $(SRC_DIR)/signals
UTILS_DIR = $(SRC_DIR)/utils

# Headers
HEADERS = $(INC_DIR)/minishell.h \
          $(INC_DIR)/types.h \
          $(INC_DIR)/ast/ast.h \
          $(INC_DIR)/builtins/exit_cmd.h \
          $(INC_DIR)/builtins/unset_cmd.h \
          $(INC_DIR)/builtins/export_cmd.h \
          $(INC_DIR)/builtins/echo_cmd.h \
          $(INC_DIR)/builtins/pwd_cmd.h \
          $(INC_DIR)/builtins/env_cmd.h \
          $(INC_DIR)/builtins/cd_cmd.h \
          $(INC_DIR)/core/core.h \
          $(INC_DIR)/core/dynamic_buffer.h \
          $(INC_DIR)/env/env.h \
          $(INC_DIR)/env/env_shlvl.h \
          $(INC_DIR)/executor/executor.h \
          $(INC_DIR)/parser/parser.h \
          $(INC_DIR)/parser/parser_errors.h \
          $(INC_DIR)/parser/parser_group.h \
          $(INC_DIR)/parser/parser_input_check.h \
          $(INC_DIR)/parser/parser_tokens.h \
          $(INC_DIR)/parser/parser_utils.h \
          $(INC_DIR)/signals/signals.h \
          $(INC_DIR)/parser/tokenizer.h \
          $(INC_DIR)/parser/tokenizer_utils.h \
          $(INC_DIR)/utils/char_utils.h \
          $(INC_DIR)/utils/get_next_line.h \
          $(INC_DIR)/utils/mem_utils.h \
          $(INC_DIR)/utils/num_utils.h \
          $(INC_DIR)/utils/path_search.h \
          $(INC_DIR)/utils/path_utils.h \
          $(INC_DIR)/utils/print.h \
          $(INC_DIR)/utils/str_utils_ext.h \
          $(INC_DIR)/utils/str_utils.h

# Source files
AST_FILES = $(AST_DIR)/ast_nodes_creation.c \
            $(AST_DIR)/ast_cmd_node_creation.c \
            $(AST_DIR)/ast_cmd_node_init.c \
            $(AST_DIR)/ast_cmd_node_init_utils.c \
            $(AST_DIR)/ast_cmd_node_utils.c \
            $(AST_DIR)/ast_ast_free.c \
            $(AST_DIR)/ast_node_error.c \
            $(AST_DIR)/ast_node_free.c \
            $(AST_DIR)/ast_node_utils.c \
            $(AST_DIR)/ast_process_ast.c

BUILTINS_FILES = $(BUILTINS_DIR)/exit_cmd.c \
                 $(BUILTINS_DIR)/unset_cmd.c \
                 $(BUILTINS_DIR)/export_cmd.c \
                 $(BUILTINS_DIR)/export_cmd_utils.c \
                 $(BUILTINS_DIR)/export_cmd_utils_ext.c \
                 $(BUILTINS_DIR)/echo_cmd.c \
                 $(BUILTINS_DIR)/echo_cmd_utils.c \
                 $(BUILTINS_DIR)/pwd_cmd.c \
                 $(BUILTINS_DIR)/env_cmd.c \
                 $(BUILTINS_DIR)/cd_cmd.c \
                 $(BUILTINS_DIR)/cd_cmd_utils.c

CORE_FILES = $(CORE_DIR)/dynamic_buffer.c \
             $(CORE_DIR)/exit_status.c \
             $(CORE_DIR)/receive_input.c

ENV_FILES = $(ENV_DIR)/env_array_utils.c \
            $(ENV_DIR)/env_array_utils_ext.c \
			$(ENV_DIR)/env_core.c \
            $(ENV_DIR)/env_default_env.c \
            $(ENV_DIR)/env_list_operations.c \
            $(ENV_DIR)/env_node_operations.c \
            $(ENV_DIR)/env_node_utils.c \
            $(ENV_DIR)/env_shlvl.c \
            $(ENV_DIR)/env_quote_handling.c \
            $(ENV_DIR)/env_quote_handling_utils.c \
            $(ENV_DIR)/env_token_processing.c \
            $(ENV_DIR)/env_utils.c \
            $(ENV_DIR)/env_validation.c \
            $(ENV_DIR)/env_setenv.c

EXECUTOR_FILES = $(EXECUTOR_DIR)/executor.c \
				$(EXECUTOR_DIR)/handle_system.c \
				$(EXECUTOR_DIR)/handle_command.c \
				$(EXECUTOR_DIR)/handle_command_pipe.c \
				$(EXECUTOR_DIR)/handle_command_redir.c \
				$(EXECUTOR_DIR)/handle_redir_process.c \
				$(EXECUTOR_DIR)/handle_command_process.c \
				$(EXECUTOR_DIR)/handle_heredoc.c \
				$(EXECUTOR_DIR)/more_execution.c \
				$(EXECUTOR_DIR)/more_execution_utils.c \
				$(EXECUTOR_DIR)/redirection_core.c \
				$(EXECUTOR_DIR)/redirection_heredoc.c \
				$(EXECUTOR_DIR)/redirection_input.c \
				$(EXECUTOR_DIR)/redirection_output.c \
				$(EXECUTOR_DIR)/utils/arg_utils.c \
                $(EXECUTOR_DIR)/utils/builtin_utils.c \
				$(EXECUTOR_DIR)/utils/command_utils.c \
				$(EXECUTOR_DIR)/utils/exit_status.c \
                $(EXECUTOR_DIR)/utils/handle_redir_utils.c \
				$(EXECUTOR_DIR)/utils/fd_utils.c \
				$(EXECUTOR_DIR)/utils/path_utils.c \
                $(EXECUTOR_DIR)/utils/path_resolve_utils.c \
				$(EXECUTOR_DIR)/utils/pipe_utils.c \
				$(EXECUTOR_DIR)/utils/system_utils.c \
				$(EXECUTOR_DIR)/utils/utils.c
				
PARSER_FILES = $(PARSER_DIR)/parser_build_ast.c \
               $(PARSER_DIR)/parser_errors.c \
               $(PARSER_DIR)/parser_group.c \
               $(PARSER_DIR)/parser_handlers.c \
               $(PARSER_DIR)/parser_handler_cmd.c \
               $(PARSER_DIR)/parser_handler_cmd_utils.c \
               $(PARSER_DIR)/parser_handler_pipe.c \
               $(PARSER_DIR)/parser_handler_redir_process.c \
               $(PARSER_DIR)/parser_argument_processor.c \
               $(PARSER_DIR)/parser_token_processor.c \
               $(PARSER_DIR)/parser_redirection_handler.c \
               $(PARSER_DIR)/parser_handler_redir.c \
               $(PARSER_DIR)/parser_handler_redir_attach.c \
               $(PARSER_DIR)/parser_handler_redir_utils.c \
               $(PARSER_DIR)/parser_input_check.c \
               $(PARSER_DIR)/parser_input_check_pipe.c \
               $(PARSER_DIR)/parser_tokens.c \
               $(PARSER_DIR)/parser_utils.c \
               $(PARSER_DIR)/parser_validate_input.c \
               $(PARSER_DIR)/tokenizer.c \
               $(PARSER_DIR)/tokenizer_expansion.c \
               $(PARSER_DIR)/tokenizer_process_token.c \
               $(PARSER_DIR)/tokenizer_utils.c \

SIGNALS_FILES = $(SIGNALS_DIR)/signal_handlers.c \
				$(SIGNALS_DIR)/signal_setup.c \
				$(SIGNALS_DIR)/signal_management.c

UTILS_FILES = $(UTILS_DIR)/char_utils.c \
              $(UTILS_DIR)/ctrl_echo.c \
              $(UTILS_DIR)/debug_print_ast.c \
              $(UTILS_DIR)/debug_print_ast_utils.c \
              $(UTILS_DIR)/debug_print_ast_node_types.c \
              $(UTILS_DIR)/get_next_line.c \
              $(UTILS_DIR)/get_next_line_utils.c \
              $(UTILS_DIR)/handle_quotes.c \
              $(UTILS_DIR)/handle_quotes_utils.c \
              $(UTILS_DIR)/mem_utils.c \
              $(UTILS_DIR)/mem_utils2.c \
              $(UTILS_DIR)/num_utils.c \
              $(UTILS_DIR)/path_search.c \
              $(UTILS_DIR)/path_utils.c \
              $(UTILS_DIR)/print_utils.c \
              $(UTILS_DIR)/str_utils_ext.c \
              $(UTILS_DIR)/str_utils_ext2.c \
              $(UTILS_DIR)/str_utils.c \
              $(UTILS_DIR)/str_utils2.c

# Combine all source files
SRC_FILES = $(AST_FILES) \
            $(BUILTINS_FILES) \
            $(CORE_FILES) \
            $(ENV_FILES) \
            $(EXECUTOR_FILES) \
            $(PARSER_FILES) \
            $(SIGNALS_FILES) \
            $(UTILS_FILES)

# Define main object file
MAIN_OBJ = $(OBJ_DIR)/main.o

# Create corresponding object files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Create necessary subdirectories in obj directory
OBJ_SUBDIRS = $(OBJ_DIR)/ast \
              $(OBJ_DIR)/builtins \
              $(OBJ_DIR)/env \
              $(OBJ_DIR)/executor \
              $(OBJ_DIR)/parser \
              $(OBJ_DIR)/signals \
              $(OBJ_DIR)/utils

# Libraries
LIBS = -lreadline

# Default target
all: create_dirs minishell

# Create directories
create_dirs:
	@printf "$(BLUE)Creating directories...$(RESET)\n"
	@mkdir -p $(OBJ_SUBDIRS)
	@mkdir -p $(BIN_DIR)

# Compile main object file
$(MAIN_OBJ): $(SRC_DIR)/main.c $(HEADERS)
	@printf "$(BLUE)Compiling main: $(RESET)%s\n" $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@printf "$(BLUE)Compiling: $(RESET)%s\n" $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Link the final executable
minishell: $(OBJ_FILES) $(MAIN_OBJ)
	@printf "$(GREEN)Linking minishell...$(RESET)\n"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	@printf "$(GREEN)Build complete: $(RESET)minishell\n"

# Clean rule
clean:
	@printf "$(BLUE)Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(BIN_DIR)/*

# Full clean rule
fclean: clean
	@printf "$(BLUE)Cleaning executable...$(RESET)\n"
	@rm -f minishell
	@rm -rf $(BIN_DIR)

# Rebuild rule
re: fclean all

# Show info rule
info:
	@printf "$(BLUE)Compiler: $(RESET)$(CC)\n"
	@printf "$(BLUE)Compiler flags: $(RESET)$(CFLAGS)\n"
	@printf "$(BLUE)Source files: $(RESET)\n"
	@for src in $(SRC_FILES); do \
		printf "  %s\n" $$src; \
	done
	@printf "$(BLUE)Object files: $(RESET)\n"
	@for obj in $(OBJ_FILES); do \
		printf "  %s\n" $$obj; \
	done

# Phony targets
.PHONY: all clean fclean re create_dirs info
