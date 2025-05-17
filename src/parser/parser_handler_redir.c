/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:57:13 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 20:10:49 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

bool		validate_redirection(t_parser_state *state, int redir_pos);
t_ast_node	*prepare_redir_node(t_parser_state *state, int redir_pos);
void		*safe_malloc(size_t size);
void		free_array(char **arr);
void		attach_redir_to_ast(t_parser_state *state, t_ast_node *redir_node);

/**
 * @brief Allocates and copies additional arguments for a command.
 *
 * @param state Pointer to the parser state structure.
 * @param cmd_node Pointer to the command node.
 * @param count Number of additional arguments.
 * @return Pointer to the new argument array, NULL if allocation fails.
 */
char	**prepare_additional_args(t_parser_state *state,
	t_ast_node *cmd_node, int count)
{
	char	**additional_args;
	int		i;
	int		j;
	int		arg_count;

	arg_count = 0;
	while (cmd_node->data.command.args
		&& cmd_node->data.command.args[arg_count])
		arg_count++;
	additional_args = safe_malloc(sizeof(char *) * (arg_count + count + 1));
	if (!additional_args)
	{
		ft_error_msg(PARSER_ERR, "Memory allocation error for additional args");
		return (NULL);
	}
	i = -1;
	while (++i < arg_count)
		additional_args[i] = ft_strdup(cmd_node->data.command.args[i]);
	j = -1;
	while (++j < count)
		additional_args[i + j] = ft_strdup(state->tokens[state->index + j]);
	additional_args[i + j] = NULL;
	return (additional_args);
}

/**
 * @brief Handles the redirection in the parser state.
 *
 * This function processes the redirection operator found at the specified
 * position in the parser state. It updates the parser state accordingly
 * to handle the redirection.
 *
 * @param state Pointer to the parser state structure.
 * @param redir_pos Position of the redirection operator in the input.
 */
void	handle_redirection(t_parser_state *state, int redir_pos)
{
	t_ast_node	*redir_node;

	if (!validate_redirection(state, redir_pos))
	{
		state->index += 2;
		return ;
	}
	redir_node = prepare_redir_node(state, redir_pos);
	if (!redir_node)
	{
		state->index += 2;
		return ;
	}
	state->index += 2;
	process_redir_arguments(state, redir_node);
	attach_redir_to_ast(state, redir_node);
}
