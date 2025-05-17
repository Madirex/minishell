/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_node_init_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:54:55 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 17:59:57 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_cmd_node_init_utils.c
 * @brief Utility functions for initializing command nodes in the AST.
 * 
 * This file contains utility functions for initializing command nodes in the
 * abstract syntax tree (AST). It includes functions for validating tokens,
 * copying tokens, and handling memory management during the initialization
 * process.
 */

#include "ast/ast.h"
#include "utils/print.h"

bool	is_redirection_token(char *token);
bool	is_pipe_token(char *token);
void	safe_free(void **ptr);
char	*ft_strdup(const char *str);

/**
 * @brief Checks if a token is valid for command arguments.
 * 
 * This function determines if a token should be included
 * in the command arguments
 * by checking if it's not empty and not a special token (pipe or redirection).
 * 
 * @param token The token to validate.
 * @return true if the token is valid, false otherwise.
 */
bool	is_valid_token(char *token)
{
	return (token && token[0] != '\0' && !is_redirection_token(token)
		&& !is_pipe_token(token));
}

/**
 * @brief Handles memory cleanup when token copying fails.
 * 
 * This function frees all previously allocated memory for command arguments
 * when a memory allocation error occurs during token copying.
 * 
 * @param args Array of command arguments.
 * @param count Number of arguments to free.
 */
static void	cleanup_args_memory(char **args, int count)
{
	while (count > 0)
	{
		safe_free((void **)&args[count - 1]);
		count--;
	}
}

/**
 * @brief Copies a single valid token into the arguments array.
 * 
 * This function duplicates a token and stores it in the arguments array.
 * If memory allocation fails, it cleans up previously allocated memory.
 * 
 * @param args Destination array for the copied token.
 * @param token Source token to copy.
 * @param index Current index in the args array.
 * @return true if copy is successful, false on memory allocation failure.
 */
bool	copy_single_token(char **args, char *token, int index)
{
	args[index] = ft_strdup(token);
	if (!args[index])
	{
		cleanup_args_memory(args, index);
		return (false);
	}
	return (true);
}
