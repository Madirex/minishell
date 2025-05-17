/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_ast_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:18:57 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:22:37 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_free.c
 * @brief Functions for freeing AST nodes and the AST itself.
 * 
 * This file contains functions for freeing AST nodes and the AST itself.
 */

#include "ast/ast.h"

void	safe_free(void **ptr);
void	ft_memset(void *ptr, int value, size_t num);

/**
 * @brief Frees an AST node.
 *
 * Recursively frees the memory allocated for an AST node and its
 * associated data based on its type.
 *
 * @param node Pointer to the AST node to free.
 * 
 * @note The function frees the memory allocated for the node and its
 * associated data, including the command name, arguments, file name,
 * and child nodes.
 */
void	free_ast_node(t_ast_node **node)
{
	if (!node)
		return ;
	if (!(*node))
	{
		return ;
	}
	if ((*node)->type == NODE_COMMAND)
	{
		free_command_node(*node);
	}
	else if ((*node)->type == NODE_PIPE)
		free_pipe_node(*node);
	else if ((*node)->type == NODE_REDIRECTION)
		free_redirection_node(*node);
	else if ((*node)->type == NODE_SUBSHELL)
		free_subshell_node(*node);
	if ((*node)->next)
	{
		free_ast_node(&(*node)->next);
	}
	safe_free((void **)node);
	*node = NULL;
}

/**
 * @brief Frees the memory allocated for an Abstract Syntax Tree (AST).
 *
 * This function frees the memory allocated for an AST, including its root node
 * and any associated syntax error information.
 *
 * @param ast Pointer to the AST to free.
 * 
 * @note If the AST pointer is NULL, a warning message is printed and 
 * the function returns without attempting to free the AST. 
 * If the AST has a root node, it is freed using the free_ast_node function.
 * Finally, the syntax error information is reset to zero.
 */
void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->root)
	{
		free_ast_node(&ast->root);
		ast->root = NULL;
	}
	ft_memset(&(ast->syntax_error), 0, sizeof(t_syntax_error));
}
