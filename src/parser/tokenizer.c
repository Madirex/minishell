/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:52:30 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 17:46:15 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/tokenizer_utils.h"
#include "utils/print.h"

bool	ft_isspace(char c);
size_t	ft_strlen(const char *s);
void	expand_tokens(char **tokens, size_t token_count, t_shell *shell);
void	ft_error_msg(const char *prefix, const char *msg);
bool	init_buffer(t_dynamic_buffer *buffer, size_t initial_capacity);
void	free_buffer(t_dynamic_buffer *buffer);
void	*safe_malloc(size_t size);
bool	process_token(const char *input, int *i, t_dynamic_buffer *buffer,
			t_tokenizer_state *state);

/**
 * @brief Initializes the tokenizer state.
 *
 * This function initializes the tokenizer state structure, allocating
 * memory for the tokens array and setting the token count to zero.
 *
 * @param input The input string to be tokenized.
 * @param token_count A pointer to an integer to store the token count.
 * @return A pointer to the newly initialized tokenizer state structure.
 *
 */
static char	**init_tokenizer(const char *input, size_t *token_count)
{
	char	**tokens;
	size_t	max_tokens;

	if (!input || !token_count)
	{
		ft_error_msg("minishell",
			"Error: Invalid input or token count pointer");
		return (NULL);
	}
	max_tokens = (ft_strlen(input) / 2) + 2;
	tokens = safe_malloc(sizeof(char *) * max_tokens);
	if (!tokens)
	{
		*token_count = 0;
		ft_error_msg("init_tokenizer", "Error: Failed to allocate memory");
		return (NULL);
	}
	*token_count = 0;
	return (tokens);
}

/**
 * @brief Handles the tokenization of the input string.
 *
 * This function processes the input string character by character,
 * building tokens based on predefined rules and delimiters.
 *
 * @param input The input string to be tokenized.
 * @param state A pointer to the tokenizer state structure.
 * @param buffer A character buffer to store the current token.
 * @return void
 *
 */
static bool	handle_tokenization(const char *input,
	t_tokenizer_state *state, t_dynamic_buffer *buffer)
{
	int		i;
	bool	success;

	i = 0;
	success = true;
	while (input[i] && success)
	{
		success = process_token(input, &i, buffer, state);
		i++;
	}
	return (success);
}

static void	init_tokenizer_state(t_tokenizer_state *state)
{
	if (!state)
		return ;
	state->tokens = NULL;
	state->token_count = 0;
	state->buffer_index = 0;
	state->quote = '\0';
	return ;
}

/**
 * @brief Finalizes the tokenization process.
 * 
 * This function finalizes the tokenization process by handling the buffer,
 * updating the tokens array, and expanding tokens with environment variables.
 * 
 * @param state The tokenizer state.
 * @param buffer The dynamic buffer.
 * @param shell The shell structure.
 * @return True if tokenization was successful, false otherwise.
 */
static bool	finalize_tokenization(t_tokenizer_state *state,
	t_dynamic_buffer *buffer, t_shell *shell)
{
	if (!state->tokens)
	{
		free_buffer(buffer);
		return (false);
	}
	handle_buffer(buffer->data, &buffer->size, state->tokens,
		&state->token_count);
	free_buffer(buffer);
	state->tokens[state->token_count] = NULL;
	expand_tokens(state->tokens, state->token_count, shell);
	return (true);
}

/**
 * @brief Tokenizes the input string into an array of tokens.
 * 
 * This function processes the input string, splitting it into tokens
 * based on the shell's environment and tokenization rules.
 * 
 * @param input The input string to tokenize.
 * @param shell The shell structure.
 * @return An array of tokens, or NULL on failure.
 * 
 * @note The returned array must be freed after use to prevent memory leaks.
 */
char	**tokenize_input(const char *input, t_shell *shell)
{
	t_tokenizer_state	state;
	t_dynamic_buffer	buffer;
	bool				success;

	if (!shell)
		return (NULL);
	init_tokenizer_state(&state);
	success = init_buffer(&buffer, BUFFER_CAPACITY);
	if (!success)
		return (NULL);
	state.tokens = init_tokenizer(input, &state.token_count);
	success = handle_tokenization(input, &state, &buffer);
	if (!success || !finalize_tokenization(&state, &buffer, shell))
	{
		free_tokens_array(state.tokens, state.token_count);
		return (NULL);
	}
	return (state.tokens);
}
