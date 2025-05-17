/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:47:08 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_utils.h
 * @brief This file contains utility functions for the parser.
 *
 * This file includes functions to check if a token is a command group,
 * balance parentheses, and get the type of redirection.
 */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "ast/ast.h"
# include "env/env.h"
# include "parser/parser_tokens.h"

bool			is_command_group(const char *token);
int				balance_parentheses(char **tokens, int *i);
t_redir_type	get_redirection_type(const char *token);

#endif
