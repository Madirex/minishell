/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_group.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:36:23 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_group.h
 * @brief This file contains the function prototypes for parsing command groups
 * in the shell.
 */

#ifndef PARSER_GROUP_H
# define PARSER_GROUP_H

# include "parser/parser.h"

t_ast_node	*parse_command_group(char **tokens, int length, t_env *cp_env);
void		handle_command_group(t_parser_state *state);

#endif
