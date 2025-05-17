/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_process_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:28:57 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/22 21:50:21 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ast_process_ast.c
 * @brief Function to process the AST.
 * 
 * This file contains the function to process the AST.
 */

#include "minishell.h"

void	build_ast(char **tokens, t_ast *ast, t_env *env);
void	execute_ast(t_ast *ast, t_shell *shell);
void	free_ast_node(t_ast_node **node);
void	print_ast_node(t_ast_node *node, int depth);

/**
 * @brief Process the AST
 * 
 * @param tokens The tokens to process
 * @param ast The AST to process
 * @param shell The shell containing environment variables
 * 
 * @note This function will build the AST, execute it and free it
 * 
 */
void	process_ast(char **tokens, t_ast *ast, t_shell *shell)
{
	build_ast(tokens, ast, shell->env);
	if (ast->root)
	{
		execute_ast(ast, shell);
		free_ast(ast);
	}
}
