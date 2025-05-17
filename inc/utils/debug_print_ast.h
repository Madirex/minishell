/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_ast.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:07:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:51:46 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file debug_print_ast.h
 * @brief This file contains functions for debugging and printing the abstract
 * syntax tree (AST) of the shell.
 */

#ifndef DEBUG_PRINT_AST_H
# define DEBUG_PRINT_AST_H

# include "../ast/ast.h"

void	print_ast(t_ast *ast);
void	print_ast_node(t_ast_node *node, int depth);
void	print_indentation(int depth);
char	*print_redirection_type(t_redir_type *redirection);
char	*get_node_type_name(t_node_type type);

// Node type printing functions
void	print_command_node(t_ast_node *node, int depth);
void	print_pipe_node(t_ast_node *node, int depth);
void	print_redirection_node(t_ast_node *node, int depth);
void	print_subshell_node(t_ast_node *node, int depth);

#endif
