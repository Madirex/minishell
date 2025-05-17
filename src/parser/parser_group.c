/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_group.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:22:13 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_group.c
 * @brief Functions for parsing command groups in the shell.
 * 
 * This file contains functions for parsing command groups in the shell.
 * 
 * A command group is a sequence of commands that are executed together.
 * Command groups are enclosed in parentheses and are treated as a single
 * command by the shell.
 * 
 */

#include "parser/parser_group.h"

void	*safe_malloc(size_t size);

/**
 * @brief Frees the memory allocated for an array of group tokens.
 *
 * This function takes an array of group tokens and its length, and
 * frees the memory allocated for each token in the array, as well as
 * the memory allocated for the array itself.
 *
 * @param group_tokens A pointer to an array of strings (group tokens)
 * to be freed.
 * @param length The number of tokens in the group_tokens array.
 * 
 * @note This function should be called after the group tokens are no longer
 * needed to prevent memory leaks.
 */
static void	free_group_tokens(char **group_tokens, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		safe_free((void **)&group_tokens[i]);
		i++;
	}
	safe_free((void **)&group_tokens);
}

/**
 * @brief Parses a command group from the given tokens.
 *
 * This function takes an array of tokens and its length, and parses them
 * to create an abstract syntax tree (AST) node representing a command group.
 *
 * @param tokens An array of strings representing the tokens to be parsed.
 * @param length The number of tokens in the array.
 * @param cp_env A pointer to the environment variables.
 * @return A pointer to the created AST node representing the command group.
 * 
 * @note The function allocates memory for the group tokens array, which
 * should be freed after use to prevent memory leaks.
 */
t_ast_node	*parse_command_group(char **tokens, int length, t_env *cp_env)
{
	t_ast		temp_ast;
	char		**group_tokens;
	int			i;

	group_tokens = safe_malloc(sizeof(char *) * (length + 1));
	if (!group_tokens)
		return (NULL);
	i = 0;
	while (i < length)
	{
		group_tokens[i] = ft_strdup(tokens[i]);
		i++;
	}
	group_tokens[i] = NULL;
	temp_ast.root = NULL;
	temp_ast.syntax_error = SYNTAX_OK;
	build_ast(group_tokens, &temp_ast, cp_env);
	free_group_tokens(group_tokens, length);
	return (temp_ast.root);
}
