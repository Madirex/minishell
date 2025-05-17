/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:20:32 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_errors.h
 * @brief This file contains the function prototypes for handling syntax errors
 * and error messages in the parser.
 */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

# include "ast/ast.h"

void	get_syntax_error_message(t_syntax_error error, const char *token);
void	handle_error(t_syntax_error error, t_shell *shell, const char *token);

#endif
