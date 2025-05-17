/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input_check.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:46:41 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_input_check.h
 * @brief This file contains functions to check the validity of input strings
 * for the parser.
 */

#ifndef PARSER_INPUT_CHECK_H
# define PARSER_INPUT_CHECK_H

bool	has_invalid_redirection(const char *input);
bool	has_invalid_pipes(const char *input);
bool	has_unclosed_quotes(const char *input);
bool	is_empty_or_whitespace(const char *input);

#endif
