/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:16:49 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast.h
 * @brief This file contains the definitions of the abstract syntax tree (AST)
 * and its associated structures and functions.
 */

#ifndef AST_H
# define AST_H

# include "types.h"
# include <stdio.h>

typedef struct s_ast_node	t_ast_node;
typedef enum e_redir_type	t_redir_type;

/**
 * @brief Command structure.
 * 
 * This structure represents a command node in the AST.
 * It contains the command name and its arguments.
 * 
 */
typedef struct s_command
{
	char	*name;
	char	**args;
}				t_command;

/**
 * @brief Pipe structure.
 * 
 * This structure represents a pipe node in the AST.
 * It contains pointers to the left and right child nodes.
 * The left child represents the command before the pipe,
 */
typedef struct s_pipe
{
	t_ast_node	*left;
	t_ast_node	*right;
}				t_pipe;

/**
 * @brief Redirection structure.
 * 
 * This structure represents a redirection node in the AST.
 * It contains the type of redirection, the file to redirect to,
 * and a pointer to the child command node.
 * The type field indicates the type of redirection (input, output, etc.).
 * The file field contains the name of the file to redirect to.
 * The child field points to the command node that is being redirected.
 */
typedef struct s_redirection
{
	t_redir_type	type;
	char			*file;
	t_ast_node		*child;
}				t_redirection;

/**
 * @brief Subshell structure.
 * 
 * This structure represents a subshell node in the AST.
 * It contains a pointer to the child node that represents the command.
 */
typedef struct s_subshell
{
	t_ast_node	*child;
}				t_subshell;

/**
 * @brief Node data union.
 * 
 * This union represents the data associated with each node in the AST.
 * Each node can hold different types of data, depending on its type.
 * The union contains:
 * - command: A command structure representing a command node.
 * - pipe: A pipe structure representing a pipe node.
 * - redirection: A redirection structure representing a redirection node.
 * - subshell: A subshell structure representing a subshell node.
 */
typedef union u_node_data
{
	t_command		command;
	t_pipe			pipe;
	t_redirection	redirection;
	t_subshell		subshell;
}				t_node_data;

/**
 * @brief AST node structure.
 * 
 * This structure represents a node in the abstract syntax tree (AST).
 * Each node can be of different types, such as command, pipe,
 * redirection, or subshell. The type field holds the type of the node,
 * and the data field holds the specific data associated with that type.
 * The env field points to the environment variables associated with the node.
 * The next field points to the next node in the list.
 * The fd_in and fd_out fields are used for input and output file descriptors.
 * The is_pipe field indicates whether the node is part of a pipe.
 */
typedef struct s_ast_node
{
	t_node_type		type;
	t_env			*env;
	t_ast_node		*next;
	t_node_data		data;
	int				fd_in;
	int				fd_out;
	bool			is_pipe;
}				t_ast_node;

/**
 * @brief AST root structure.
 * 
 * This structure represents the root of the abstract syntax tree (AST).
 * It contains a pointer to the root node and a syntax error structure.
 * The syntax error structure contains information about any syntax errors
 * that may have occurred during parsing.
 */
typedef struct s_ast
{
	t_ast_node		*root;
	t_syntax_error	syntax_error;
}				t_ast;

void		append_node(t_ast_node **head, t_ast_node *new_node);
void		append_argument(t_ast_node *cmd_node, const char *new_arg);
t_ast_node	*allocate_node(t_node_type type);
bool		copy_tokens(char **tokens, t_ast_node *node, int token_count);
t_ast_node	*create_cmd_node(char **arguments, t_env *env);
t_ast_node	*create_pipe_node(t_ast_node *leftCmd, t_ast_node *rightCmd);
t_ast_node	*create_redir_node(t_redir_type redirection, char *file,
				t_ast_node *childCmd);
t_ast_node	*create_subshell_node(t_ast_node *childCmd);
void		free_ast(t_ast *ast);
void		free_ast_node(t_ast_node **node);
void		free_cmd_args(char **args, int index);
void		free_command_node(t_ast_node *node);
void		free_pipe_node(t_ast_node *node);
void		free_redirection_node(t_ast_node *node);
void		free_subshell_node(t_ast_node *node);
void		handle_allocation_error(t_node_type type);
void		process_ast(char **tokens, t_ast *ast, t_shell *shell);
bool		set_command_name(char **tokens, t_ast_node *node);

#endif
