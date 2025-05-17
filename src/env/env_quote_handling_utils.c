/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_handling_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:45:56 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/09 13:20:27 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_quote_handling_utils.c
 * @brief Functions for handling quotes and environment variables in input
 * strings.
 */

#include "env/env.h"
#include "core/dynamic_buffer.h"
#include "types.h"

static bool	handle_special_cases(t_token_context *ctx,
				t_dynamic_buffer *buffer);

/**
 * @brief Handles the variable name and appends its value to the buffer.
 * 
 * This function retrieves the variable name and its value from the environment.
 * It appends the value to the buffer. If the variable name is NULL, an empty
 * string is appended to the buffer.
 * 
 * @param ctx Token context.
 * @param buffer Destination buffer.
 * @param var_name The variable name to handle.
 */
static void	handle_var_name(t_token_context *ctx,
	t_dynamic_buffer *buffer, char *var_name)
{
	char	*var_value;

	if (var_name == NULL)
	{
		append_to_buffer(buffer, "", 0);
		return ;
	}
	var_value = get_env_value(var_name, ctx->env);
	if (var_value)
		append_to_buffer(buffer, var_value, ft_strlen(var_value));
	else
		append_to_buffer(buffer, "", 0);
	ctx->ptr += ft_strlen(var_name);
	safe_free((void **)&var_name);
}

/**
 * @brief Adds the variable value to the buffer.
 * 
 * This function handles the special case of the exit status variable.
 * 
 * @param ctx Token context.
 * @param buffer Destination buffer.
 * @param var_value The variable value to add.
 * 
 * This function is responsible for handling the special case of the exit
 * status variable. It converts the exit status to a string and appends it
 * to the buffer. The function also handles memory management by freeing
 * the variable value after use.
 * 
 */
void	add_var_value(t_token_context *ctx, t_dynamic_buffer *buffer,
	char *var_value)
{
	char	*status_str;

	if (var_value)
	{
		append_to_buffer(buffer, var_value, ft_strlen(var_value));
		return ;
	}
	status_str = ft_itoa(ctx->shell->exit_status);
	if (status_str)
	{
		append_to_buffer(buffer, status_str, ft_strlen(status_str));
		safe_free((void **)&status_str);
	}
	ctx->ptr++;
}

/**
 * @brief Handles environment variables in the input string.
 * 
 * This function processes environment variables and expands them.
 * 
 * @param ctx Token context.
 * @param buffer Destination buffer.
 */
void	handle_env_variable(t_token_context *ctx, t_dynamic_buffer *buffer)
{
	char	*var_name;

	ctx->ptr++;
	if (handle_special_cases(ctx, buffer))
		return ;
	var_name = get_env_name(ctx->ptr);
	if (var_name == NULL || ft_strlen(var_name) == 0)
	{
		append_to_buffer(buffer, "", 0);
		safe_free((void **)&var_name);
		return ;
	}
	handle_var_name(ctx, buffer, var_name);
}

/**
 * @brief Handles special cases for variable expansion.
 * 
 * This function checks for special cases like `$?` and `$`.
 * 
 * @param ctx Token context.
 * @param buffer Destination buffer.
 * @return true if a special case was handled, false otherwise.
 */
static bool	handle_special_cases(t_token_context *ctx, t_dynamic_buffer *buffer)
{
	if (*ctx->ptr == '?')
	{
		add_var_value(ctx, buffer, NULL);
		return (true);
	}
	if (*ctx->ptr == '$')
	{
		append_to_buffer(buffer, "$", 1);
		ctx->ptr++;
		return (true);
	}
	return (false);
}

/**
 * @brief Handles exit status variable expansion inside double quotes.
 * 
 * @param ctx Token context.
 * @param buffer Destination buffer.
 */
void	handle_exit_status_in_quotes(t_token_context *ctx,
	t_dynamic_buffer *buffer)
{
	char	*status_str;

	status_str = ft_itoa(ctx->shell->exit_status);
	if (status_str)
	{
		append_to_buffer(buffer, status_str, ft_strlen(status_str));
		safe_free((void **)&status_str);
	}
	ctx->ptr += 2;
}
