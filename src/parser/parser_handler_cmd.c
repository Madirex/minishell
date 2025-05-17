/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:54:02 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/22 21:55:31 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_handler_cmd.c
 * @brief This file contains functions for handling command tokens in the
 *        Abstract Syntax Tree (AST) of a shell parser.
 */

#include "minishell.h"
#include "parser/parser.h"

void	*safe_malloc(size_t size);
size_t	get_token_count(t_parser_state *state);
void	copy_command_tokens(char **cmd_tokens, t_parser_state *state,
			int start, int token_count);
bool	is_valid_state(t_parser_state *state);

/**
 * @file parser_handler_cmd.c
 * @brief Functions for handling command tokens in the parser state.
 * 
 * This file contains functions for handling command tokens in the parser state.
 * 
 * A command token is a sequence of characters that represents a shell command.
 * Command tokens are used to build the abstract syntax tree (AST) for the shell.
 * 
 */

static void	validate_and_allocate_tokens(t_parser_state *state,
	char ***cmd_tokens, int *start, int *token_count)
{
	if (!is_valid_state(state))
		return ;
	*start = state->index;
	*token_count = get_token_count(state);
	*cmd_tokens = allocate_command_tokens(*token_count);
	if (!*cmd_tokens)
		return ;
}

static void	process_command_tokens(t_parser_state *state,
	char **cmd_tokens, int start, int token_count)
{
	copy_command_tokens(cmd_tokens, state, start, token_count);
}

static t_ast_node	*create_command_node(t_parser_state *state,
	char **cmd_tokens)
{
	t_ast_node	*cmd_node;

	cmd_node = create_cmd_node(cmd_tokens, state->env);
	if (!cmd_node)
	{
		free_array(cmd_tokens);
		return (NULL);
	}
	return (cmd_node);
}

static void	attach_command_node(t_parser_state *state, t_ast_node *cmd_node)
{
	t_ast_node	*current;

	if (!state->ast->root)
		state->ast->root = cmd_node;
	else if (state->ast->root->type == NODE_REDIRECTION)
	{
		current = state->ast->root;
		while (current->data.redirection.child
			&& current->data.redirection.child->type == NODE_REDIRECTION)
		{
			current = current->data.redirection.child;
		}
		current->data.redirection.child = cmd_node;
	}
	else
		append_node(&state->ast->root, cmd_node);
	state->last_node = cmd_node;
	state->last_command_node = cmd_node;
}

void	handle_command(t_parser_state *state)
{
	char		**cmd_tokens;
	t_ast_node	*cmd_node;
	int			start;
	int			token_count;

	validate_and_allocate_tokens(state, &cmd_tokens, &start, &token_count);
	if (!cmd_tokens)
		return ;
	process_command_tokens(state, cmd_tokens, start, token_count);
	cmd_node = create_command_node(state, cmd_tokens);
	if (!cmd_node)
		return ;
	attach_command_node(state, cmd_node);
	free_array(cmd_tokens);
}
