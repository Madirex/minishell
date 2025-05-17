/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_process_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:11:44 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 17:36:17 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/tokenizer_utils.h"
#include "utils/print.h"
#include "core/dynamic_buffer.h"

bool	ft_isspace(char c);
void	ft_error_msg(const char *prefix, const char *msg);
bool	append_char_to_buffer(t_dynamic_buffer *buffer, char c);

bool	process_token(const char *input, int *i, t_dynamic_buffer *buffer,
	t_tokenizer_state *state)
{
	if ((input[*i] == '"' || input[*i] == '\'') && !state->quote)
		state->quote = input[*i];
	else if (input[*i] == state->quote)
		state->quote = 0;
	else if (ft_isspace(input[*i]) && !state->quote)
	{
		handle_buffer(buffer->data, &buffer->size, state->tokens,
			&state->token_count);
		buffer->size = 0;
		buffer->data[0] = '\0';
		return (true);
	}
	else if ((input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
		&& !state->quote)
	{
		handle_special_characters(input, i, buffer, state);
		return (true);
	}
	if (!append_char_to_buffer(buffer, input[*i]))
		return (false);
	return (true);
}
