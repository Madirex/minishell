/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:30:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/02 10:45:07 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_quote_handling.c
 * @brief Functions for handling quotes and environment variables in input
 * strings.
 */

#include "env/env.h"

void	handle_exit_status_in_quotes(t_token_context *ctx,
			t_dynamic_buffer *buffer);
void	add_var_value(t_token_context *ctx, t_dynamic_buffer *buffer,
			char *var_value);
void	handle_double_quotes(t_token_context *ctx,
			t_dynamic_buffer *buffer);

/**
 * @brief Handles single quotes in the input string.
 * 
 * In single quotes, no variable expansion is done.
 * This implementation copies the quotes into the result.
 * 
 * @param ctx Token context.
 * @param buffer Destination buffer.
 */
void	handle_single_quotes(t_token_context *ctx, t_dynamic_buffer *buffer)
{
	const char	*start;

	append_to_buffer(buffer, "'", 1);
	ctx->ptr++;
	start = ctx->ptr;
	while (*ctx->ptr && *ctx->ptr != '\'')
		ctx->ptr++;
	append_to_buffer(buffer, start, ctx->ptr - start);
	if (*ctx->ptr == '\'')
	{
		append_to_buffer(buffer, "'", 1);
		ctx->ptr++;
	}
}

/**
 * @brief Process double quote contents character by character.
 * 
 * @param ctx Token context.
 * @param buffer Destination buffer.
 */
static void	process_dquote_contents(t_token_context *ctx,
	t_dynamic_buffer *buffer)
{
	while (*ctx->ptr && *ctx->ptr != '"')
	{
		if (*ctx->ptr == '$' && (ft_isalnum(*(ctx->ptr + 1))
				|| *(ctx->ptr + 1) == '?' || *(ctx->ptr + 1) == '$'))
		{
			if (*(ctx->ptr + 1) == '?')
				handle_exit_status_in_quotes(ctx, buffer);
			else
				handle_env_variable(ctx, buffer);
		}
		else
		{
			append_to_buffer(buffer, ctx->ptr, 1);
			ctx->ptr++;
		}
	}
}

/**
 * @brief Handles double quotes in the input string.
 * 
 * In double quotes, variable expansion is done.
 * This implementation copies the quotes into the result.
 * 
 * @param ctx Token context.
 * @param buffer Destination buffer.
 */
void	handle_double_quotes(t_token_context *ctx, t_dynamic_buffer *buffer)
{
	append_to_buffer(buffer, "\"", 1);
	ctx->ptr++;
	process_dquote_contents(ctx, buffer);
	if (*ctx->ptr == '"')
	{
		append_to_buffer(buffer, "\"", 1);
		ctx->ptr++;
	}
}
