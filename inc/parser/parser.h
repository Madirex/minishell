/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:47:58 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.h
 * @brief This file contains the parser functions.
 */

#ifndef PARSER_H
# define PARSER_H

# include "parser/parser_tokens.h"

char		**allocate_command_tokens(size_t token_count);
void		attach_redir_to_ast(t_parser_state *state, t_ast_node *redir_node);
void		build_ast(char **tokens, t_ast *ast, t_env *cp_env);
int			count_additional_args(t_parser_state *state);
int			count_cmd_args(t_ast_node *right_node);
void		handle_argument(t_parser_state *state, const char *token);
void		handle_command(t_parser_state *state);
void		handle_current_token(t_parser_state *state);
void		handle_pipe(t_parser_state *state);
void		handle_redirection(t_parser_state *state, int redir_pos);
t_ast_node	*process_additional_args(t_parser_state *state,
				t_ast_node *right_node);
char		**prepare_additional_args(t_parser_state *state,
				t_ast_node *cmd_node, int count);
bool		process_redir_arguments(t_parser_state *state,
				t_ast_node *redir_node);

#endif
