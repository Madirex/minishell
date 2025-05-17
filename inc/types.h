/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:03:01 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 17:18:43 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file types.h
 * @brief This file contains the definitions of various types used in the shell.
 * 
 * This file includes the definition of the abstract syntax tree (AST) node,
 * environment variables, and other structures used in the shell.
 * It also includes enumerations for node types, redirection types, 
 * and syntax errors.
 */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_ast		t_ast;
typedef struct s_ast_node	t_ast_node;

/**
 * @brief Represents an element in the list of environment variables.
 * 
 * This structure represents an environment variable in the shell.
 * It contains a key, a value, and a pointer to the next environment variable.
 * The key is a string that represents the name of the variable.
 * The value is a string that represents the value of the variable.
 * The next pointer points to the next environment variable in the list.
 * The is_freed flag indicates whether the variable has been freed or not.
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	bool			is_freed;
}				t_env;

/**
 * @brief This is the main structure of the shell.
 * 
 * This structure contains the environment variables, the abstract syntax tree,
 * and the exit status.
 * The env pointer points to the list of environment variables.
 * The ast pointer points to the root of the abstract syntax tree.
 * The exit_status is an integer that keeps the exit status 
 * of the last command.
 */
typedef struct s_shell
{
	t_env		*env;
	t_ast		*ast;
	int			exit_status;
}				t_shell;

/**
 * @brief Node type enumeration.
 * 
 * This enumeration defines the types of nodes in the abstract syntax tree.
 * Each node can be one of the following types:
 * - NODE_COMMAND: Represents a command node.
 * - NODE_PIPE: Represents a pipe node.
 * - NODE_REDIRECTION: Represents a redirection node.
 * - NODE_SUBSHELL: Represents a subshell node.
 */
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECTION,
	NODE_SUBSHELL
}			t_node_type;

/**
 * @brief Redirection type enumeration.
 * 
 * This enumeration defines the types of redirections that can 
 * occur in the shell.
 * Each redirection can be one of the following types:
 * - REDIR_INPUT: Represents input redirection.
 * - REDIR_OUTPUT: Represents output redirection.
 * - REDIR_APPEND: Represents append redirection.
 * - REDIR_HEREDOC: Represents here-document redirection.
 * - REDIR_NONE: Represents no redirection.
 */
typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_NONE
}				t_redir_type;

/**
 * @brief Syntax error enumeration.
 * 
 * This enumeration defines the types of syntax errors that can occur
 * during parsing.
 * Each error can be one of the following types:
 * - SYNTAX_OK: No syntax error.
 * - SYNTAX_EMPTY: Empty syntax.
 * - SYNTAX_UNEXPECTED_TOKEN: Unexpected token in the syntax.
 * - SYNTAX_MISSING_OPERATOR: Missing operator in the syntax.
 * - SYNTAX_MISSING_COMMAND: Missing command in the syntax.
 * - SYNTAX_UNCLOSED_QUOTE: Unclosed quote in the syntax.
 * - SYNTAX_UNCLOSED_SUBSHELL: Unclosed subshell in the syntax.
 * - SYNTAX_COMMAND_NOT_FOUND: Command not found in the syntax.
 */
typedef enum e_syntax_error
{
	SYNTAX_OK,
	SYNTAX_EMPTY,
	SYNTAX_UNEXPECTED_TOKEN,
	SYNTAX_MISSING_OPERATOR,
	SYNTAX_MISSING_COMMAND,
	SYNTAX_UNCLOSED_QUOTE,
	SYNTAX_UNCLOSED_SUBSHELL,
	SYNTAX_COMMAND_NOT_FOUND
}			t_syntax_error;

/**
 * @brief Signal state enumeration.
 * 
 * This enumeration defines the states of signals that can be received
 * by the shell. Each state can be one of the following types:
 * - SIG_NONE: No signal received.
 * - SIG_INT: Interrupt signal (SIGINT).
 * - SIG_QUIT: Quit signal (SIGQUIT).
 * - SIG_EOF: End-of-file signal (EOF).
 */
typedef enum e_signal_state
{
	SIG_NONE = 0,
	SIG_INT = 1,
	SIG_QUIT = 1 << 1,
	SIG_EOF = 1 << 2
}				t_signal_state;

/**
 * @brief Dynamic buffer structure.
 * 
 * This structure represents a dynamic buffer that can be expanded as needed.
 * It contains a pointer to the data, the current size, and the 
 * allocated capacity.
 * The data is a character pointer that stores the buffer contents.
 * The size is the current length of the data in the buffer.
 * The capacity is the total allocated size of the buffer.
 */
typedef struct s_dynamic_buffer
{
	char	*data;
	size_t	size;
	size_t	capacity;
}				t_dynamic_buffer;

/**
 * @brief Parser state structure.
 * 
 * This structure represents the state of the parser during parsing.
 * It contains a list of tokens, the current index in the token list,
 * the abstract syntax tree, the last node processed, the last command node,
 * and the environment variables.
 * 
 * The last_command_node element is used to keep track of the most
 * recent command node encountered during parsing. This allows the parser
 * to efficiently attach redirections or arguments to the correct command
 * node as it processes the input tokens, ensuring that the abstract syntax 
 * tree accurately represents the structure of the shell command being parsed.
 */
typedef struct s_parser_state
{
	char		**tokens;
	int			index;
	t_ast		*ast;
	t_ast_node	*last_node;
	t_ast_node	*last_command_node;
	t_env		*env;
}				t_parser_state;

/**
 * @brief Token context structure.
 * 
 * This structure represents the context of tokenization.
 * It contains a pointer to the current position in the input string,
 * a pointer to the environment variables, a pointer to the shell,
 * the current variable value, the current variable name,
 * and flags indicating whether inside single or double quotes.
 */
typedef struct s_token_context
{
	const char	*ptr;
	t_env		*env;
	t_shell		*shell;
	char		*current_var_value;
	char		*current_var;
	bool		in_single_quote;
	bool		in_double_quote;
}				t_token_context;

/**
 * @brief Tokenizer state structure.
 * 
 * This structure represents the state of the tokenizer during tokenization.
 * It contains an array of tokens, the number of tokens, the current index
 * in the buffer, and the current quote character.
 */
typedef struct s_tokenizer_state
{
	char	**tokens;
	size_t	token_count;
	size_t	buffer_index;
	char	quote;
}				t_tokenizer_state;

#endif
