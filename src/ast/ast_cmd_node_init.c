/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_node_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:28:31 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 18:06:37 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_cmd_node_init.c
 * @brief Functions for initializing command nodes in the AST.
 * 
 * This file contains functions for initializing command nodes in the
 * abstract syntax tree (AST). It includes functions for counting
 * valid tokens, allocating memory for command arguments, and copying
 * valid tokens into the command arguments array.
 */

#include "ast/ast.h"
#include "utils/print.h"

void	*safe_malloc(size_t size);
bool	is_valid_token(char *token);
bool	copy_single_token(char **args, char *token, int index);
bool	is_redirection_token(const char *token);
bool	is_pipe_token(const char *token);
void	safe_free(void **ptr);

/**
 * @brief Copies valid tokens into the command arguments array.
 * 
 * This function iterates through the tokens array, copying valid tokens
 * into the provided args array while skipping redirection and pipe tokens.
 * It uses helper functions to validate tokens, handle memory management,
 * and perform the actual copying.
 * 
 * @param tokens Array of tokens to process.
 * @param args Array to store the copied valid tokens.
 * @return true if all tokens are successfully copied, false otherwise.
 */
static bool	copy_valid_tokens(char **tokens, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (is_redirection_token(tokens[i]))
			i += 2;
		else if (is_pipe_token(tokens[i]))
			i++;
		else if (is_valid_token(tokens[i]))
		{
			if (!copy_single_token(args, tokens[i], j++))
				return (false);
			i++;
		}
		else
			i++;
	}
	args[j] = NULL;
	return (true);
}

/**
 * @brief Allocates memory for the command arguments in the AST node.
 * 
 * This function allocates memory for the command arguments based on the
 * provided token count and assigns it to the AST node's command data.
 * 
 * @param node Pointer to the AST node.
 * @param token_count Number of valid tokens to allocate memory for.
 * @return true if memory allocation is successful, false otherwise.
 */
static bool	allocate_command_args(t_ast_node *node, int token_count)
{
	node->data.command.args = safe_malloc(sizeof(char *) * (token_count + 1));
	if (!node->data.command.args)
	{
		ft_error_msg(AST_ERR, "Failed to allocate memory for args");
		return (false);
	}
	return (true);
}

/**
 * @brief Counts the valid tokens in the input array.
 * 
 * This function iterates through the tokens array, identifying valid tokens
 * while skipping redirection and pipe tokens. The count of valid tokens is
 * stored in the provided token_count pointer.
 * 
 * @param tokens Array of tokens to process.
 * @param token_count Pointer to an integer to store the count of valid tokens.
 * @return true if the operation is successful, false otherwise.
 */
static bool	count_valid_tokens(char **tokens, int *token_count)
{
	int	i;

	i = 0;
	*token_count = 0;
	if (!tokens)
		return (false);
	while (tokens[i])
	{
		if (is_redirection_token(tokens[i]))
		{
			i += 2;
			if (!tokens[i])
				break ;
		}
		else if (is_pipe_token(tokens[i]))
			i++;
		else
		{
			(*token_count)++;
			i++;
		}
	}
	return (true);
}

/**
 * @brief Initializes the command data for a given AST node.
 * 
 * This function counts the valid tokens, allocates memory 
 * for the command arguments, and copies the valid tokens
 * into the allocated memory.
 * 
 * @param node Pointer to the AST node to initialize.
 * @param tokens Array of tokens to process.
 * @return true if the initialization is successful, false otherwise.
 */
bool	init_command_data(t_ast_node *node, char **tokens)
{
	int	token_count;

	if (!count_valid_tokens(tokens, &token_count))
		return (false);
	if (!allocate_command_args(node, token_count))
		return (false);
	if (!copy_valid_tokens(tokens, node->data.command.args))
	{
		safe_free((void **)&node->data.command.args);
		return (false);
	}
	return (true);
}

/**
 * @brief Initializes the command node with the provided tokens.
 * 
 * This function initializes the command data of the AST node by processing
 * the provided tokens. If initialization fails, the allocated memory for
 * the command name is freed.
 * 
 * @param node Pointer to the AST node to initialize.
 * @param tokens Array of tokens to process.
 * @return true if the initialization is successful, false otherwise.
 */
bool	initialize_command_node(t_ast_node *node, char **tokens)
{
	if (!init_command_data(node, tokens))
	{
		ft_error_msg(AST_ERR, "Failed to initialize command data");
		safe_free((void **)&node->data.command.name);
		return (false);
	}
	return (true);
}
