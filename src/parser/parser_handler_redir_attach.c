/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_redir_attach.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:42:07 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 20:00:03 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_handler_redir_attach.c
 * @brief This file contains functions for attaching redirection nodes to the
 *        Abstract Syntax Tree (AST) in a parser.
 */

#include "parser/parser.h"

/**
 * @brief Initializes the AST root with the given redirection node.
 *
 * This function sets the root of the Abstract Syntax Tree (AST) to the
 * provided redirection node and updates the last node in the parser state.
 *
 * @param state Pointer to the parser state structure, which contains the AST.
 * @param redir_node Pointer to the redirection node to be set as the AST root.
 */
static void	initialize_ast_root(t_parser_state *state, t_ast_node *redir_node)
{
	state->ast->root = redir_node;
	state->last_node = redir_node;
}

/**
 * @brief Attaches a redirection node to the root command node in the AST.
 *
 * This function integrates the redirection node into the AST when the root
 * node is a command node. The redirection node becomes the new root, and the
 * previous root is set as its child.
 *
 * @param state Pointer to the parser state structure, which contains the AST.
 * @param redir_node Pointer to the redirection node to be attached.
 */
static void	attach_to_command_root(t_parser_state *state,
	t_ast_node *redir_node)
{
	redir_node->data.redirection.child = state->ast->root;
	state->ast->root = redir_node;
	state->last_node = redir_node;
}

/**
 * @brief Traverses the AST and attaches a redirection node.
 *
 * This function traverses the AST to find the appropriate position to attach
 * the redirection node. It handles cases where the AST contains nested
 * redirection nodes.
 *
 * @param state Pointer to the parser state structure, which contains the AST.
 * @param current_node Pointer to the current node being traversed in the AST.
 * @param redir_node Pointer to the redirection node to be attached.
 */
static void	traverse_and_attach(t_parser_state *state,
	t_ast_node *current_node, t_ast_node *redir_node)
{
	while (current_node->type == NODE_REDIRECTION
		&& current_node->data.redirection.child
		&& current_node->data.redirection.child->type == NODE_REDIRECTION)
	{
		current_node = current_node->data.redirection.child;
	}
	if (current_node->type == NODE_REDIRECTION)
	{
		redir_node->data.redirection.child = current_node
			->data.redirection.child;
		current_node->data.redirection.child = redir_node;
	}
	else
	{
		redir_node->data.redirection.child = current_node;
		state->ast->root = redir_node;
	}
	state->last_node = redir_node;
}

/**
 * @brief Attaches a redirection node to the Abstract Syntax Tree (AST).
 *
 * This function is responsible for attaching a redirection node to the AST.
 * It ensures that the redirection node is properly integrated into the tree,
 * handling cases where the AST root is null, the root is a command node, or
 * the root contains nested redirection nodes.
 *
 * @param state Pointer to the parser state structure, which contains the AST.
 * @param redir_node Pointer to the redirection node to be attached to the AST.
 *
 * @note The function modifies the AST root and updates the last node in the
 *       parser state to the newly attached redirection node.
 */
void	attach_redir_to_ast(t_parser_state *state, t_ast_node *redir_node)
{
	t_ast_node	*current_node;

	if (!state->ast->root)
	{
		initialize_ast_root(state, redir_node);
		return ;
	}
	if (state->ast->root->type == NODE_COMMAND)
	{
		attach_to_command_root(state, redir_node);
		return ;
	}
	current_node = state->ast->root;
	traverse_and_attach(state, current_node, redir_node);
}
