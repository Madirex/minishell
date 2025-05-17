/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:44:14 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:23:55 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_nodes_creation.c
 * 
 * This file contains functions for creating different types of AST nodes.
 * 
 * The functions in this file are used to create nodes for commands, pipes,
 * redirections, and subshells in the abstract syntax tree (AST).
 * 
 */

#include "ast/ast.h"

void	safe_free(void **ptr);

/**
* Creates a pipe node in the abstract syntax tree (AST) using the given
* left and right command nodes.
*
* @param leftCmd A pointer to the left command node in the AST.
* @param rightCmd A pointer to the right command node in the AST.
* @return A pointer to the created pipe node in the AST, or NULL if either
* child is NULL.
* 
* @note The function allocates memory for the new node and sets the left
* and right child nodes accordingly.
*/
t_ast_node	*create_pipe_node(t_ast_node *leftCmd, t_ast_node *rightCmd)
{
	t_ast_node	*node;

	if (!leftCmd || !rightCmd)
		return (NULL);
	node = allocate_node(NODE_PIPE);
	if (!node)
		return (NULL);
	node->data.pipe.left = leftCmd;
	node->data.pipe.right = rightCmd;
	node->next = NULL;
	node->env = NULL;
	return (node);
}

/**
* @brief Creates a redirection AST node.
*
* This function creates a new AST (Abstract Syntax Tree) node for handling
* redirections in a shell command. The node will contain information about
* the type of redirection, the file involved, and the child command node.
*
* @param redirection The type of redirection (e.g., input, output, append).
* @param file The file associated with the redirection.
* @param childCmd The child command node that this redirection applies to.
* @return A pointer to the newly created redirection AST node.
*
* @note The file parameter must be a valid string, and the redirection type
* must be one of the supported redirection types.
*/
t_ast_node	*create_redir_node(t_redir_type redirection, char *file,
	t_ast_node *childCmd)
{
	t_ast_node	*node;

	if (!file || (redirection != REDIR_OUTPUT && redirection
			!= REDIR_INPUT && redirection != REDIR_APPEND && redirection
			!= REDIR_HEREDOC))
	{
		safe_free((void **)&file);
		return (NULL);
	}
	node = allocate_node(NODE_REDIRECTION);
	if (!node)
	{
		safe_free((void **)&file);
		return (NULL);
	}
	node->data.redirection.type = redirection;
	node->data.redirection.file = file;
	node->data.redirection.child = childCmd;
	node->next = NULL;
	node->env = NULL;
	return (node);
}

/**
* @brief Creates a subshell AST node.
*
* This function creates a new AST (Abstract Syntax Tree)
* node representing a subshell command. If the child command
* is NULL, the function returns NULL as a subshell must contain
* a valid command.
*
* @param childCmd A pointer to the AST node representing the child command.
* @return A pointer to the newly created subshell AST node, or NULL if
* childCmd is NULL.
*
* @note The child command node is expected to be a valid command node.
*/
t_ast_node	*create_subshell_node(t_ast_node *childCmd)
{
	t_ast_node	*node;

	if (!childCmd)
		return (NULL);
	node = allocate_node(NODE_SUBSHELL);
	if (!node)
	{
		free_ast_node(&childCmd);
		return (NULL);
	}
	node->data.subshell.child = childCmd;
	node->next = NULL;
	node->env = NULL;
	return (node);
}
