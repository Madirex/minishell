/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:22:55 by airyago           #+#    #+#             */
/*   Updated: 2025/03/20 13:35:04 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_node_management.c
 * @brief Functions to manage the AST nodes.
 * 
 * This file contains functions to manage the AST nodes.
 */

#include "ast/ast.h"

void	free_ast_node(t_ast_node **node);
void	free_ast(t_ast *ast);
void	safe_free(void **ptr);

/**
 * @brief Frees a command node.
 *
 * Frees the memory allocated for a command node, including the command name
 * and arguments.
 *
 * @param node Pointer to the command node to free.
 * 
 * @note The function frees the memory allocated for the command name and
 * arguments, and sets the corresponding pointers to NULL.
 */
void	free_command_node(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->data.command.name)
	{
		safe_free((void **)&node->data.command.name);
	}
	if (node->data.command.args)
	{
		i = 0;
		while (node->data.command.args[i])
		{
			safe_free((void **)&node->data.command.args[i]);
			i++;
		}
		safe_free((void **)&node->data.command.args);
	}
}

/**
 * @brief Frees a redirection node.
 *
 * Frees the memory allocated for a redirection node, including the file
 * name and child node.
 *
 * @param node Pointer to the redirection node to free.
 * 
 * @note The function frees the memory allocated for the file name and child
 * node, and sets the corresponding pointers to NULL.
 */
void	free_redirection_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->data.redirection.file)
	{
		safe_free((void **)&node->data.redirection.file);
		node->data.redirection.file = NULL;
	}
	if (node->data.redirection.child)
	{
		free_ast_node(&node->data.redirection.child);
		node->data.redirection.child = NULL;
	}
}

/**
 * @brief Frees a subshell node.
 *
 * Frees the memory allocated for a subshell node, including
 * its child node.
 *
 * @param node Pointer to the subshell node to free.
 * 
 * @note The function frees the memory allocated for the child node,
 * and sets the corresponding pointer to NULL.
 */
void	free_subshell_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->data.subshell.child)
	{
		free_ast_node(&node->data.subshell.child);
		node->data.subshell.child = NULL;
	}
}

/**
 * @brief Frees a pipe node.
 *
 * Frees the memory allocated for a pipe node, including the left
 * and right child nodes.
 *
 * @param node Pointer to the pipe node to free.
 * 
 * @note The function frees the memory allocated for the left and right
 * child nodes, and sets the corresponding pointers to NULL.
 */
void	free_pipe_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->data.pipe.left)
	{
		free_ast_node(&node->data.pipe.left);
		node->data.pipe.left = NULL;
	}
	if (node->data.pipe.right)
	{
		free_ast_node(&node->data.pipe.right);
		node->data.pipe.right = NULL;
	}
}
