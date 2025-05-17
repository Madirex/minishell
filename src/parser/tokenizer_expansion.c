/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:54:06 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/27 16:50:01 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * 	@file tokenizer_expansion.c
 * 	@brief Function for expanding environment variables in tokens.
 */

#include "types.h"

char	*replace_env_variables(const char *token, t_shell *shell);
void	safe_free(void **ptr);

/**
 * @brief Expands tokens by replacing environment variables.
 * 
 * This function iterates through an array of tokens, replacing any
 * environment variables found within each token with their corresponding
 * values from the environment variables list.
 * 
 * @param tokens Array of tokens to process.
 * @param token_count Number of tokens in the array.
 * @param shell The shell structure.
 */
void	expand_tokens(char **tokens, size_t token_count, t_shell *shell)
{
	size_t	i;
	char	*expanded_token;

	if (!shell || !shell->env)
		return ;
	i = 0;
	while (i < token_count)
	{
		expanded_token = replace_env_variables(tokens[i], shell);
		safe_free((void **)&tokens[i]);
		tokens[i] = expanded_token;
		i++;
	}
}
