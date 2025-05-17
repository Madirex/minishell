/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/20 20:03:13 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @file parser_utils.c
 * * @brief Utility functions for the parser.
 * 
 */

#include "parser/parser_utils.h"

/**
 * @brief Checks the balance of parentheses in the given tokens.
 *
 * This function iterates through the provided tokens and checks if 
 * the parentheses are balanced. It updates the index pointer to reflect the 
 * current position in the tokens.
 *
 * @param tokens An array of strings representing the tokens to be checked.
 * @param i A pointer to an int representing the current index 
 * in the tokens array.
 * @return The starting index of the command group if parentheses are balanced,
 * or -1 if the parentheses are unbalanced.
 * 
 */
int	balance_parentheses(char **tokens, int *i)
{
	int	parentheses_count;
	int	start;

	parentheses_count = 1;
	start = *i + 1;
	while (tokens[*i] && parentheses_count > 0)
	{
		(*i)++;
		if (tokens[*i])
		{
			if (tokens[*i][0] == '(')
				parentheses_count++;
			else if (tokens[*i][0] == ')')
				parentheses_count--;
		}
	}
	if (parentheses_count > 0)
		return (-1);
	return (start);
}

/**
 * @brief Handles a command group in the parser state.
 *
 * This function processes a command group within the given parser state.
 *
 * @param state A pointer to the parser state structure.
 * 
 * @note A command group is a sequence of commands enclosed in parentheses.
 * It is treated as a single command in the abstract syntax tree (AST).
 */
void	handle_command_group(t_parser_state *state)
{
	int			start;
	t_ast_node	*subshell_content;
	t_ast_node	*subshell_node;

	start = balance_parentheses(state->tokens, &state->index);
	if (start == -1)
	{
		state->ast->syntax_error = SYNTAX_UNCLOSED_SUBSHELL;
		return ;
	}
	subshell_content = parse_command_group(&state->tokens[start],
			state->index - start, state->env);
	subshell_node = create_subshell_node(subshell_content);
	if (state->last_node == NULL)
		state->ast->root = subshell_node;
	else
		append_node(&state->ast->root, subshell_node);
	state->last_node = subshell_node;
}

/**
 * @brief Determines the type of redirection based on the given token.
 *
 * This function takes a token as input and returns the corresponding
 * redirection type. The token is expected to be a string representing
 * a redirection operator (e.g., ">", ">>", "<", "<<").
 *
 * @param token The token representing the redirection operator.
 * @return The type of redirection as a value of the t_redir_type enum.
 * 
 * @note If the token does not match any known redirection operator,
 * the function returns REDIR_NONE.
 */
t_redir_type	get_redirection_type(const char *token)
{
	if (!token)
	{
		ft_error_msg(PARSER_ERR, "Invalid token in get_redirection_type");
		return (REDIR_NONE);
	}
	else if (ft_strcmp(token, "<<") == 0)
		return (REDIR_HEREDOC);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_APPEND);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUTPUT);
	else if (ft_strcmp(token, "<") == 0)
		return (REDIR_INPUT);
	ft_error_msg(PARSER_ERR, "Invalid token in get_redirection_type");
	return (REDIR_NONE);
}
