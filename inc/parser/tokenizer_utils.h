/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:42 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 17:40:46 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer_utils.h
 * @brief This file contains utility functions for the tokenizer.
 */

#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

# include "types.h"
# include <stdio.h>

# define BUFFER_CAPACITY 65536

void	free_tokens_array(char **tokens, int count);
char	*duplicate_input(const char *input);
void	process_quotes(char **token, char *quote);
void	finalize_tokens(char **tokens, char *start, int *i);
void	handle_buffer(char *buffer, size_t *buffer_index, char **tokens,
			size_t *token_count);
void	handle_special_characters(const char *input, int *i, t_dynamic_buffer *buffer,
			t_tokenizer_state *state);

#endif
