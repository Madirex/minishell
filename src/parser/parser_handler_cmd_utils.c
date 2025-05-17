/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_cmd_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:18:59 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 19:57:58 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @file parser_handler_cmd_utils.c
 * * @brief This file contains utility functions for handling command tokens
 * *        in the parser.
 */

#include "minishell.h"
#include "parser/parser.h"

void	*safe_malloc(size_t size);
void	free_array(char **array);
void	ft_error_msg(const char *prefix, const char *msg);
bool	is_redirection_token(const char *token);
bool	is_operator_token(const char *token);

/**
 * @brief Checks if the parser state is valid.
 * 
 * This function checks if the parser state is valid and contains the necessary
 * information to process command tokens.
 * 
 * @param state A pointer to the parser state structure.
 * @return true if the state is valid, false otherwise.
 * 
 * @note This function is used internally by the handle_command function.
 */
bool	is_valid_state(t_parser_state *state)
{
	if (!state || !state->tokens || state->index < 0
		|| !state->tokens[state->index])
	{
		ft_error_msg(PARSER_ERR, "Invalid state or tokens");
		return (false);
	}
	return (true);
}

/**
 * @brief Gets the number of tokens in the command.
 * 
 * This function calculates the number of tokens in the command starting
 * from the current position in the parser state.
 * 
 * @param state A pointer to the parser state structure.
 * @return The number of tokens in the command.
 * 
 * @note This function is used internally by the handle_command function.
 */
size_t	get_token_count(t_parser_state *state)
{
	size_t	token_count;
	int		i;

	token_count = 0;
	i = state->index;
	while (state->tokens[i])
	{
		if (is_redirection_token(state->tokens[i]))
		{
			i += 2;
			continue ;
		}
		if (is_operator_token(state->tokens[i]))
			break ;
		token_count++;
		i++;
	}
	return (token_count);
}

/**
 * @brief Allocates memory for the command tokens.
 * 
 * This function allocates memory for the command tokens based on the
 * number of tokens in the command.
 * 
 * @param token_count The number of tokens in the command.
 * @return A pointer to the allocated command tokens array.
 * 
 * @note This function is used internally by the handle_command function.
 */
char	**allocate_command_tokens(size_t token_count)
{
	char	**cmd_tokens;

	cmd_tokens = safe_malloc(sizeof(char *) * (token_count + 1));
	if (!cmd_tokens)
	{
		ft_error_msg(PARSER_ERR, "Memory allocation error");
		return (NULL);
	}
	return (cmd_tokens);
}

/**
 * @brief Copies the command tokens from the parser state.
 * 
 * This function copies the command tokens from the parser state to the
 * allocated command tokens array.
 * 
 * @param cmd_tokens A pointer to the command tokens array.
 * @param state A pointer to the parser state structure.
 * @param start The starting position of the command tokens in the state.
 * @param token_count The number of tokens in the command.
 * 
 * @note This function is used internally by the handle_command function.
 */
void	copy_command_tokens(char **cmd_tokens, t_parser_state *state,
	int start, int token_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < token_count && state->tokens[start + i])
	{
		if (is_redirection_token(state->tokens[start + i]))
		{
			i += 2;
			continue ;
		}
		if (is_operator_token(state->tokens[start + i]))
			break ;
		cmd_tokens[j] = ft_strdup(state->tokens[start + i]);
		j++;
		i++;
	}
	cmd_tokens[j] = NULL;
	state->index = start + i;
}
