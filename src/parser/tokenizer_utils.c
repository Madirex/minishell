/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:53:31 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 17:41:15 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer_utils.c
 * 
 * This file contains utility functions for the tokenizer module.
 * 
 * The tokenizer module is responsible for breaking down the input string
 * into individual tokens based on predefined rules and delimiters.
 * 
 * The functions in this file provide support for tokenizing the input string,
 * handling special characters, and freeing the tokens array.
 * 
 */

#include "parser/tokenizer_utils.h"
#include "utils/print.h"

char	*ft_strdup(const char *s);
void	safe_free(void **ptr);
bool	append_char_to_buffer(t_dynamic_buffer *buffer, char c);

/**
 * @brief Frees an array of tokens.
 *
 * This function takes an array of tokens and the count of tokens,
 * and frees each token in the array, then frees the array itself.
 *
 * @param tokens The array of tokens to be freed.
 * @param count The number of tokens in the array.
 * 
 * @note If the count is -1, the function will free all tokens until
 * it encounters a NULL pointer.
 */
void	free_tokens_array(char **tokens, int count)
{
	int	i;

	if (!tokens || !*tokens)
		return ;
	i = 0;
	if (count == -1)
	{
		while (tokens[i])
		{
			safe_free((void **)&tokens[i]);
			i++;
		}
	}
	else
	{
		while (i < count)
		{
			safe_free((void **)&tokens[i]);
			i++;
		}
	}
	safe_free((void **)&tokens);
}

/**
 * @brief Duplicates the given input string.
 *
 * This function creates a duplicate of the input string by allocating
 * memory for the new string and copying the contents of the input string
 * into the newly allocated memory.
 *
 * @param input The input string to be duplicated.
 * @return A pointer to the newly allocated string containing the duplicate
 * of the input string. If memory allocation fails, returns NULL.
 * 
 * @note The caller is responsible for freeing the returned string when it is
 * no longer needed.
 */
char	*duplicate_input(const char *input)
{
	char	*input_copy;

	input_copy = ft_strdup(input);
	if (!input_copy)
		ft_error_msg(PARSER_ERR, "ft_strdup failed");
	return (input_copy);
}

/**
 * @brief Handles the buffer by performing necessary operations.
 *
 * This function processes the buffer and updates the buffer index.
 *
 * @param buffer A pointer to the buffer that needs to be handled.
 * @param buffer_index A pointer to the index of the buffer to update.
 * @param tokens An array of tokens to store the buffer contents.
 * @param token_count A pointer to the token count to update.
 * 
 * @note This function is used to tokenize the input string.
 */
void	handle_buffer(char *buffer, size_t *buffer_index,
	char **tokens, size_t *token_count)
{
	if (*buffer_index > 0)
	{
		buffer[*buffer_index] = '\0';
		tokens[(*token_count)++] = ft_strdup(buffer);
		*buffer_index = 0;
	}
}

/**
 * @brief Handles special characters in the input string.
 *
 * This function processes special characters in the input string and updates
 * the index accordingly. It is used to parse and tokenize the input string
 * for further processing.
 *
 * @param input The input string to be processed.
 * @param i Pointer to the current index in the input string. This index will
 * be updated based on the special characters encountered.
 * @param buffer A pointer to the buffer to store the special characters.
 * @param state A pointer to the tokenizer state structure.
 * 
 * @note This function is used to tokenize the input string.
 */
void	handle_special_characters(const char *input, int *i,
	t_dynamic_buffer *buffer, t_tokenizer_state *state)
{
	char	*new_token;

	if (buffer->size > 0)
	{
		buffer->data[buffer->size] = '\0';
		new_token = ft_strdup(buffer->data);
		if (!new_token)
			return (ft_error_msg(PARSER_ERR, "ft_strdup failed"));
		state->tokens[state->token_count++] = new_token;
		buffer->size = 0;
		buffer->data[0] = '\0';
	}
	if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
	{
		append_char_to_buffer(buffer, input[(*i)++]);
	}
	append_char_to_buffer(buffer, input[*i]);
	buffer->data[buffer->size] = '\0';
	new_token = ft_strdup(buffer->data);
	if (!new_token)
		return (ft_error_msg(PARSER_ERR, "ft_strdup failed"));
	state->tokens[state->token_count++] = new_token;
	buffer->size = 0;
	buffer->data[0] = '\0';
}
