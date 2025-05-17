/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_ast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/22 21:54:12 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @file parser_build_ast.c
 * * @brief This file contains functions for building the Abstract Syntax Tree
 *        (AST) from the tokenized input in a parser.
 */

#include "parser/parser.h"

void	print_tokens(char **tokens);
void	print_ast(t_ast *ast); //DEBUG

/**
 * @brief Initializes the parser state structure.
 * 
 * This function initializes the parser state structure with the provided
 * tokens, abstract syntax tree (AST), and environment variables.
 * 
 * @param state A pointer to the parser state structure to be initialized.
 * 
 * @return true if the state is successfully initialized, false otherwise.
 * 
 * @note This function is used internally by the build_ast function.
 */
bool	init_state(t_parser_state *state, char **tokens,
	t_ast *ast, t_env *env)
{
	if (!tokens || !ast || !env)
	{
		ft_error_msg(PARSER_ERR, "Invalid parameters in init_state");
		return (false);
	}
	state->tokens = tokens;
	state->ast = ast;
	state->last_node = NULL;
	state->env = env;
	state->index = 0;
	return (true);
}

/**
 * @brief builds the abstract syntax tree (AST) from the tokenized input.
 * 
 * This function processes the tokenized input and builds the abstract syntax 
 * tree (AST) for the shell commands. The AST is used to represent the structure
 * of the commands and their relationships, such as pipes and redirections.
 * 
 * @param tokens An array of strings representing the tokenized input.
 * @param ast A pointer to the abstract syntax tree (AST) structure.
 * @param cp_env A pointer to the environment structure containing environment
 * variables.
 * 
 * @note This function uses the parser state structure to keep track of the
 * current state of the parser and the tokens being processed. 
 */
void	build_ast(char **tokens, t_ast *ast, t_env *cp_env)
{
	t_parser_state	state;

	if (!tokens || !ast || !cp_env)
	{
		ft_error_msg(PARSER_ERR, "Invalid parameters in build_ast");
		return ;
	}
	if (!init_state(&state, tokens, ast, cp_env))
	{
		ft_error_msg(PARSER_ERR, "Failed to initialize parser state");
		return ;
	}
	ast->syntax_error = SYNTAX_OK;
	while (state.tokens[state.index] && ast->syntax_error == SYNTAX_OK)
		handle_current_token(&state);
}
