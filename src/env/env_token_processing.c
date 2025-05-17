/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:24:27 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/02 10:46:09 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @file env_token_processing.c
 * 
 * * This file contains functions for processing tokens in the context of
 * * environment variable replacement. It includes functions for handling
 * * single and double quotes, as well as replacing environment variables
 * * with their corresponding values.
 */

#include "env/env.h"

bool	init_buffer(t_dynamic_buffer *buffer, size_t initial_capacity);
bool	free_buffer(t_dynamic_buffer *buffer);
void	*safe_malloc(size_t size);

/**
 * * @brief Handles single quotes in the input string.
 * * @param ctx Token context.
 * * @param buffer Destination buffer.
 * *
 * * @note This function handles environment variables inside single quotes.
 */
static void	copy_exit_status(t_token_context *ctx, t_dynamic_buffer *buffer)
{
	char	*status_str;
	size_t	value_len;
	int		status;

	status = 0;
	if (ctx && ctx->shell)
		status = ctx->shell->exit_status;
	status_str = ft_itoa(status);
	if (status_str)
	{
		value_len = ft_strlen(status_str);
		append_to_buffer(buffer, status_str, value_len);
		safe_free((void **)&status_str);
	}
}

/**
 * @brief Processes a character in the input string.
 * @param ctx Token context.
 * @param buffer Destination buffer.
 * 
 * This function processes a character in the input string, handling
 * special characters, quotes, and environment variables.
 * 
 * @note This function is used by the replace_env_variables function.
 * 
 */
static void	process_token_char(t_token_context *ctx, t_dynamic_buffer *buffer)
{
	if (*ctx->ptr == '$' && *(ctx->ptr + 1) == '?')
	{
		copy_exit_status(ctx, buffer);
		ctx->ptr += 2;
	}
	else if (*ctx->ptr == '\'' && !ctx->in_double_quote)
	{
		ctx->in_single_quote = !ctx->in_single_quote;
		handle_single_quotes(ctx, buffer);
	}
	else if (*ctx->ptr == '"' && !ctx->in_single_quote)
	{
		ctx->in_double_quote = !ctx->in_double_quote;
		handle_double_quotes(ctx, buffer);
	}
	else if (*ctx->ptr == '$' && !ctx->in_single_quote && *(ctx->ptr + 1)
		&& (ft_isalnum(*(ctx->ptr + 1)) || *(ctx->ptr + 1) == '_'))
		handle_env_variable(ctx, buffer);
	else
	{
		append_to_buffer(buffer, ctx->ptr, 1);
		ctx->ptr++;
	}
}

/**
 * * @brief Frees the token context structure.
 * * @param ctx Pointer to the token context structure to free.
 * 
 * * This function frees the memory allocated for the token context
 * * structure and sets the pointer to NULL.
 * * @note This function should be called when the token context is no
 * * longer needed to prevent memory leaks.
 */
void	free_token_context(t_token_context **ctx)
{
	if (!ctx || !*ctx)
		return ;
	safe_free((void **) ctx);
	*ctx = NULL;
}

/**
 * @brief Initializes a token context structure.
 * 
 * This function initializes a token context structure with the specified
 * token and environment variables list, setting the initial state of the
 * context and allocating memory for the structure.
 * 
 * @param token The token to process.
 * @param env The environment variables list.
 * @param shell The shell structure.
 * 
 * @return A pointer to the initialized token context structure.
 * 
 * @note The returned structure must be freed after use to prevent memory leaks.
 */
t_token_context	*init_token_context(const char *token, t_env *env,
		t_shell *shell)
{
	t_token_context	*ctx;

	ctx = safe_malloc(sizeof(t_token_context));
	if (!ctx)
		return (NULL);
	ctx->ptr = token;
	ctx->env = env;
	ctx->shell = shell;
	ctx->current_var_value = NULL;
	ctx->current_var = NULL;
	ctx->in_single_quote = false;
	ctx->in_double_quote = false;
	return (ctx);
}

/**
 * @brief Replaces environment variables in a token.
 * 
 * This function processes a token, replacing any environment variables
 * found within it with their corresponding values from the environment
 * variables list.
 * 
 * @param token Token to process.
 * @param shell The shell structure.
 * @return The token with environment variables replaced.
 * 
 * @note The returned token must be freed after use to prevent memory leaks.
 */
char	*replace_env_variables(const char *token, t_shell *shell)
{
	t_token_context		*ctx;
	t_dynamic_buffer	buffer;
	char				*result;

	if (!token)
		return (ft_strdup(""));
	if (!shell || !shell->env)
		return (ft_strdup(token));
	ctx = init_token_context(token, shell->env, shell);
	if (!ctx)
		return (ft_strdup(token));
	if (!init_buffer(&buffer, INITIAL_BUFFER_SIZE))
	{
		free_token_context(&ctx);
		return (ft_strdup(token));
	}
	while (*ctx->ptr)
		process_token_char(ctx, &buffer);
	result = buffer.data;
	buffer.data = NULL;
	free_buffer(&buffer);
	free_token_context(&ctx);
	return (result);
}
