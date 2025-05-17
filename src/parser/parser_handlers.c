/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:56:52 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/11 12:44:53 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_handlers.c
 * @brief Contains functions to handle the current token in the parser state.
 * 
 */

#include "parser/parser.h"

bool	is_argument_token(const char *token, t_parser_state *state);
void	*safe_malloc(size_t size);

/**
 * @brief Allocates memory for a new argument array and copies the old arguments.
 * 
 * This function allocates memory for a new argument array, copies the old
 * arguments into it, and appends a new argument at the end. The new array is
 * null-terminated.
 * 
 * @param old_args Pointer to the old argument array.
 * @param new_arg Pointer to the new argument string to append.
 * @param arg_count Number of arguments in the old array.
 * @return Pointer to the newly allocated argument array, or NULL on failure.
 * 
 * @note The function does not check if the old_args or new_arg are NULL.
 */
static char	**allocate_new_args(char **old_args, const char *new_arg,
	int arg_count)
{
	char	**new_args;

	new_args = safe_malloc(sizeof(char *) * (arg_count + 2));
	if (!new_args)
	{
		ft_error_msg(PARSER_ERR,
			"Error: Memory allocation failed in append_argument()");
		return (NULL);
	}
	ft_memcpy(new_args, old_args, sizeof(char *) * arg_count);
	new_args[arg_count] = ft_strdup(new_arg);
	new_args[arg_count + 1] = NULL;
	return (new_args);
}

/**
 * @brief Initializes the command node's arguments with a new argument.
 * 
 * This function takes a command node and a new argument string,
 * and initializes the command node's arguments with the new argument.
 * If memory allocation fails, an error message is printed.
 * 
 * @param cmd_node Pointer to the command node.
 * @param new_arg Pointer to the new argument string to initialize.
 * 
 * @note The function does not check if the command node is NULL.
 * It is the caller's responsibility to ensure that the command node
 * is valid before calling this function.
 */
static void	initialize_args(t_ast_node *cmd_node, const char *new_arg)
{
	cmd_node->data.command.args = safe_malloc(sizeof(char *) * 2);
	if (!cmd_node->data.command.args)
	{
		ft_error_msg(PARSER_ERR,
			"Error: Memory allocation failed in append_argument()");
		return ;
	}
	cmd_node->data.command.args[0] = ft_strdup(new_arg);
	cmd_node->data.command.args[1] = NULL;
}

/**
 * @brief Appends a new argument to the command node's arguments.
 * 
 * This function takes a command node and a new argument string,
 * and appends the new argument to the command node's arguments.
 * If the command node's arguments are NULL, it initializes them
 * with the new argument. If memory allocation fails, an error
 * message is printed.
 * 
 * @param cmd_node Pointer to the command node.
 * @param new_arg Pointer to the new argument string to append.
 * 
 * @note The function does not check if the command node is NULL.
 * It is the caller's responsibility to ensure that the command node
 * is valid before calling this function.
 */
void	append_argument(t_ast_node *cmd_node, const char *new_arg)
{
	char	**new_args;
	int		arg_count;

	if (!cmd_node || !new_arg)
		return ;
	if (!cmd_node->data.command.args)
	{
		initialize_args(cmd_node, new_arg);
		return ;
	}
	arg_count = 0;
	while (cmd_node->data.command.args[arg_count])
		arg_count++;
	new_args = allocate_new_args(cmd_node->data.command.args,
			new_arg, arg_count);
	if (!new_args)
		return ;
	safe_free((void **)&cmd_node->data.command.args);
	cmd_node->data.command.args = new_args;
}

/**
 * @brief Handles the argument token in the parser state.
 *
 * This function processes the argument token in the given parser state.
 *
 * @param state A pointer to the parser state structure.
 * @param token The argument token to be handled.
 * 
 * @note The function updates the parser state to handle the argument token.
 */
void	handle_argument(t_parser_state *state, const char *token)
{
	t_ast_node	*current_node;

	if (!state || !token || !state->last_command_node)
		return ;
	current_node = state->last_command_node;
	if (current_node->type == NODE_COMMAND)
		append_argument(current_node, token);
	else
		ft_error_msg(PARSER_ERR, "Syntax error: Argument with no command");
	state->index++;
}

/**
 * @brief Handles the current token in the parser state.
 *
 * This function processes the current token in the given parser state.
 *
 * @param state A pointer to the parser state structure.
 * 
 * @note The function updates the parser state to handle the current token.
 */
void	handle_current_token(t_parser_state *state)
{
	const char	*token;

	token = state->tokens[state->index];
	if (is_command_group(token))
		handle_command_group(state);
	else if (is_pipe_token(token))
		handle_pipe(state);
	else if (is_redirection_token(token))
		handle_redirection(state, state->index);
	else if (is_argument_token(token, state))
		handle_argument(state, token);
	else
		handle_command(state);
	if (state->ast->syntax_error != SYNTAX_OK)
		get_syntax_error_message(state->ast->syntax_error,
			state->tokens[state->index]);
	return ;
}
