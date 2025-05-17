/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_processor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:40:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/13 19:45:58 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_token_processor.c
 * @brief Functions for processing command tokens for the parser.
 */

#include "parser/parser.h"

void	*safe_malloc(size_t size);
void	free_array(char **arr);

/**
 * @brief Counts the number of tokens in the command.
 * 
 * This function calculates the number of tokens in the command starting
 * from the current position in the parser state.
 * 
 * @param state Pointer to the parser state structure.
 * @return The number of tokens in the command.
 */
int	count_command_tokens(t_parser_state *state)
{
	int	count;

	count = 0;
	while (state->tokens[state->index]
		&& !is_pipe_token(state->tokens[state->index])
		&& !is_redirection_token(state->tokens[state->index]))
	{
		count++;
		state->index++;
	}
	return (count);
}

/**
 * @brief Isolates the command tokens and allocates memory for them.
 * 
 * This function allocates memory for the command tokens array based on the
 * number of tokens in the command.
 * 
 * @param state Pointer to the parser state structure.
 * @param start_index The starting index of the command tokens in the state.
 * @param count The number of tokens in the command.
 * @return A pointer to the allocated command tokens array.
 */
char	**extract_command_tokens(t_parser_state *state,
	int start_index, int count)
{
	int		i;
	char	**cmd_tokens;

	cmd_tokens = allocate_command_tokens(count);
	if (!cmd_tokens)
	{
		ft_error_msg(PARSER_ERR, "Memory allocation error in handle_pipe");
		state->ast->syntax_error = SYNTAX_UNEXPECTED_TOKEN;
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		cmd_tokens[i] = ft_strdup(state->tokens[start_index + i]);
		i++;
	}
	cmd_tokens[count] = NULL;
	return (cmd_tokens);
}

/**
 * @brief Creates and initializes the command node for a pipe.
 * 
 * @param state Parser state.
 * @return Command node or NULL if creation fails.
 */
t_ast_node	*initialize_pipe_command(t_parser_state *state)
{
	int			start_index;
	int			count;
	char		**cmd_tokens;
	t_ast_node	*right_node;

	start_index = state->index;
	count = count_command_tokens(state);
	cmd_tokens = extract_command_tokens(state, start_index, count);
	if (!cmd_tokens)
		return (NULL);
	right_node = create_cmd_node(cmd_tokens, state->env);
	free_array(cmd_tokens);
	return (right_node);
}

/**
 * @brief Increments the index in the parser state and checks for errors.
 * 
 * @param state Pointer to the parser state structure.
 * 
 * @note This function increments the index in the parser state and checks
 * if the next token is an operator or a pipe.
 */
void	increment_index_and_check(t_parser_state *state)
{
	state->index++;
	if (!state->tokens[state->index]
		|| is_operator_token(state->tokens[state->index]))
	{
		ft_error_msg(PARSER_ERR,
			"Syntax error: Pipe must be followed by a command");
		state->ast->syntax_error = SYNTAX_MISSING_COMMAND;
	}
}

/**
 * @brief Creates a pipe structure with the given right node.
 * 
 * This function creates a pipe structure with the given right node and
 * returns a pointer to the created pipe node.
 * 
 * @param state Pointer to the parser state structure.
 * @param right_node Pointer to the right node of the pipe.
 * @return The created pipe node or NULL if failed.
 */
t_ast_node	*create_pipe_structure(t_parser_state *state,
	t_ast_node *right_node)
{
	t_ast_node	*pipe_node;

	if (!right_node)
		return (NULL);
	pipe_node = NULL;
	if (!state->ast->root)
		pipe_node = create_pipe_node(NULL, right_node);
	else
		pipe_node = create_pipe_node(state->ast->root, right_node);
	if (!pipe_node)
		ft_error_msg(PARSER_ERR, "Failed to create pipe node");
	return (pipe_node);
}
