/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argument_processor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:50:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 20:01:50 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_argument_processor.c
 * @brief Functions for processing additional arguments for commands.
 */

#include "parser/parser.h"

void	*safe_malloc(size_t size);
void	free_array(char **arr);

/**
 * @brief Counts additional arguments after a redirection.
 *
 * @param state Pointer to the parser state structure.
 * @return Number of additional arguments.
 */
int	count_additional_args(t_parser_state *state)
{
	int	count;
	int	i;

	count = 0;
	i = state->index;
	while (state->tokens[i] && !is_redirection_token(state->tokens[i])
		&& !is_pipe_token(state->tokens[i]))
	{
		count++;
		i++;
	}
	return (count);
}

/**
 * @brief Count arguments in the command node.
 * 
 * @param right_node The command node.
 * @return Number of arguments in the command.
 */
int	count_cmd_args(t_ast_node *right_node)
{
	int	j;

	j = 0;
	while (right_node->data.command.args
		&& right_node->data.command.args[j])
		j++;
	return (j);
}

/**
 * @brief Allocates memory for additional arguments.
 * 
 * @param right_node The command node.
 * @param count Number of additional arguments.
 * @return Allocated array for arguments.
 */
char	**allocate_additional_args(t_ast_node *right_node, int count)
{
	int		arg_count;
	char	**additional_args;

	arg_count = count_cmd_args(right_node);
	additional_args = safe_malloc(sizeof(char *) * (arg_count + count + 1));
	if (!additional_args)
	{
		ft_error_msg(PARSER_ERR,
			"Memory allocation error for additional args");
		return (NULL);
	}
	return (additional_args);
}

/**
 * @brief Copies existing arguments to new array and adds new arguments.
 * 
 * @param additional_args Target array.
 * @param right_node Source command node.
 * @param state Parser state with tokens.
 * @param count Number of arguments to add.
 */
void	copy_arguments(char **additional_args, t_ast_node *right_node,
	t_parser_state *state, int count)
{
	int	i;
	int	j;

	i = 0;
	while (right_node->data.command.args && right_node->data.command.args[i])
	{
		additional_args[i] = ft_strdup(right_node->data.command.args[i]);
		i++;
	}
	j = 0;
	while (j < count)
	{
		additional_args[i + j] = ft_strdup(state->tokens[state->index + j]);
		j++;
	}
	additional_args[i + j] = NULL;
}

/**
 * @brief Process additional arguments after redirection.
 * 
 * @param state Parser state.
 * @param right_node Command node to update.
 * @return Updated node or NULL on error.
 */
t_ast_node	*process_additional_args(t_parser_state *state,
	t_ast_node *right_node)
{
	int		count;
	char	**additional_args;

	if (!state->tokens[state->index]
		|| is_redirection_token(state->tokens[state->index])
		|| is_pipe_token(state->tokens[state->index]))
		return (right_node);
	count = count_additional_args(state);
	additional_args = allocate_additional_args(right_node, count);
	if (!additional_args)
		return (NULL);
	copy_arguments(additional_args, right_node, state, count);
	free_array(right_node->data.command.args);
	right_node->data.command.args = additional_args;
	state->index += count;
	return (right_node);
}
