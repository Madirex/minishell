/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_node_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:37:15 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 13:33:28 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_cmd_node_utils.c
 * 
 * This file contains utility functions for managing command nodes in the AST.
 * 
 * The functions in this file are used to set the command name and arguments
 * in the AST node representing a command.
 */

#include "ast/ast.h"
#include "utils/print.h"

char	*ft_strdup(const char *s);
void	safe_free(void **ptr);
void	*safe_malloc(size_t size);

/**
* @brief Frees command arguments up to a specified index
*
* @param args Array of command arguments to free
* @param index Index up to which to free (exclusive)
*
* @note This function frees the memory allocated for the command arguments
*/
void	free_cmd_args(char **args, int index)
{
	while (index > 0)
	{
		index--;
		safe_free((void **)&args[index]);
	}
	safe_free((void **)&args);
}

/**
* @brief Sets the command name in the AST node.
*
* @param tokens An array of strings representing the tokens.
* @param node A pointer to the AST node where the command name will be set.
* @return An integer indicating the success or failure of the operation.
* 
* @note The function returns 0 on success, -1 on failure.
*/
bool	set_command_name(char **tokens, t_ast_node *node)
{
	if (tokens[0] == NULL)
	{
		ft_error_msg(PARSER_ERR, "No command name provided");
		return (false);
	}
	if (node->data.command.name)
		safe_free((void **)&node->data.command.name);
	node->data.command.name = ft_strdup(tokens[0]);
	if (!node->data.command.name)
	{
		ft_error_msg(PARSER_ERR, "ft_strdup failed");
		return (false);
	}
	return (true);
}

/**
* @brief Copies tokens into the AST node's command arguments.
*
* @param tokens Array of strings representing the command tokens.
* @param node Pointer to the AST node where the tokens will be copied.
* @param token_count Number of tokens to copy.
* @return true on success, false on failure.
*
* @note This function allocates memory for the command arguments and copies
* the tokens into the node.
*/
bool	copy_tokens(char **tokens, t_ast_node *node, int token_count)
{
	int		i;

	node->data.command.args = safe_malloc(sizeof(char *) * (token_count + 1));
	i = 0;
	while (i < token_count)
	{
		node->data.command.args[i] = ft_strdup(tokens[i]);
		if (!node->data.command.args[i])
		{
			while (i > 0)
			{
				safe_free((void *) node->data.command.args[i - 1]);
				i--;
			}
			safe_free((void *)node->data.command.args);
			return (false);
		}
		i++;
	}
	node->data.command.args[token_count] = NULL;
	return (true);
}
