/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:46:59 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_tokens.h
 * @brief This file contains functions to check the type of tokens in the parser.
 */

#ifndef PARSER_TOKENS_H
# define PARSER_TOKENS_H

# include "ast/ast.h"
# include "utils/str_utils.h"

bool	is_pipe_token(const char *token);
bool	is_redirection_token(const char *token);
bool	is_operator_token(const char *token);

#endif
