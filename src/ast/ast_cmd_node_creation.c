/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_node_creation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:28:31 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 14:08:30 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_cmd_node_creation.c
 * @brief Functions for creating and managing command nodes in the AST.
 * 
 * This file contains functions for creating command nodes in the abstract syntax
 * tree (AST). It includes functions for initializing command data, allocating
 * memory for command arguments, and copying valid tokens from the input.
 */

#include "ast/ast.h"
#include "utils/print.h"

char	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);
bool	initialize_command_node(t_ast_node *node, char **tokens);

/**
 * @brief Allocates memory for a new command node in the AST.
 * 
 * This function creates a new AST node of type NODE_COMMAND and initializes
 * its memory. If memory allocation fails, an error message is logged.
 * 
 * @return Pointer to the allocated AST node, or NULL on failure.
 */
static t_ast_node	*allocate_command_node(void)
{
	t_ast_node	*node;

	node = allocate_node(NODE_COMMAND);
	if (!node)
	{
		ft_error_msg(AST_ERR, "Failed to allocate memory for AST node");
	}
	return (node);
}

/**
 * @brief Sets the command name in the AST node.
 * 
 * This function duplicates the provided command name and assigns it to the
 * command data of the AST node. If memory allocation fails, an error message
 * is logged.
 * 
 * @param node Pointer to the AST node.
 * @param command_name Command name to set in the node.
 * @return true if the operation is successful, false otherwise.
 */
static bool	set_command_name_in_node(t_ast_node *node, char *command_name)
{
	node->data.command.name = ft_strdup(command_name);
	if (!node->data.command.name)
	{
		ft_error_msg(AST_ERR, "Failed to allocate memory for command name");
		return (false);
	}
	return (true);
}

/**
 * @brief Creates a command node in the AST.
 * 
 * This function allocates memory for a command node, sets the command name,
 * initializes the command data, and assigns the environment pointer.
 * 
 * @param tokens Array of tokens to process.
 * @param cp_env Pointer to the environment structure.
 * @return Pointer to the created command node, or NULL on failure.
 */
t_ast_node	*create_cmd_node(char **tokens, t_env *cp_env)
{
	t_ast_node	*node;

	if (!tokens || !tokens[0])
	{
		ft_error_msg(AST_ERR, "NULL tokens received in create_cmd_node()");
		return (NULL);
	}
	node = allocate_command_node();
	if (!node)
		return (NULL);
	if (!set_command_name_in_node(node, tokens[0]))
	{
		free_ast_node(&node);
		return (NULL);
	}
	if (!initialize_command_node(node, tokens))
	{
		free_ast_node(&node);
		return (NULL);
	}
	node->env = cp_env;
	return (node);
}
