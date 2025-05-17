/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:01:05 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 19:42:20 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_handler_pipe.c
 * @brief This file contains the main function for handling pipe operators
 *        in the parser state.
 */

#include "parser/parser.h"

/* External function declarations */
void		increment_index_and_check(t_parser_state *state);
t_ast_node	*initialize_pipe_command(t_parser_state *state);
t_ast_node	*process_pipe_redirections(t_parser_state *state,
				t_ast_node *right_node);
t_ast_node	*create_pipe_structure(t_parser_state *state,
				t_ast_node *right_node);

/**
 * @brief Handles the pipe operator in the parser state.
 * 
 * This function processes the pipe operator found at the specified position
 * in the parser state. It updates the parser state accordingly.
 * 
 * @param state Pointer to the parser state structure.
 */
void	handle_pipe(t_parser_state *state)
{
	t_ast_node	*right_node;
	t_ast_node	*pipe_node;

	increment_index_and_check(state);
	if (state->ast->syntax_error)
		return ;
	right_node = initialize_pipe_command(state);
	if (!right_node)
		return ;
	right_node = process_pipe_redirections(state, right_node);
	if (!right_node)
		return ;
	pipe_node = create_pipe_structure(state, right_node);
	if (pipe_node)
	{
		state->ast->root = pipe_node;
		state->last_node = pipe_node;
	}
}
