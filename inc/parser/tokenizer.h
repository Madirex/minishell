/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:00:30 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:48:29 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer.h
 * @brief This file contains the definitions of the tokenizer functions.
 * 
 */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "types.h"

char	**tokenize_input(const char *input, t_shell *shell);
void	expand_tokens(char **tokens, size_t token_count, t_shell *shell);

#endif
