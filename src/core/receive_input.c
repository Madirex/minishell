/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:28:57 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/01 11:31:53 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser_input_check.h"

bool	is_sigint_received(void);
void	clear_sigint(void);
void	ft_putstr_fd(const char *s, int fd);
bool	validate_input(char *input);
void	handle_error(t_syntax_error error, t_shell *shell, const char *token);

/**
 * @brief Tokenizes the user's input into an array of strings.
 * 
 * This function splits the user input into tokens using the tokenizer utility
 * functions, which consider special shell characters and syntax. If 
 * tokenization fails, an error message is displayed.
 * 
 * @param input The user input string to be tokenized.
 * @param shell A pointer to the shell structure containing
 * environment variables and exit status.
 * @return An array of strings representing the tokens, or NULL if 
 * tokenization fails.
 * 
 * @note Ensure the returned tokens array is freed after use to prevent 
 * memory leaks.
 */
static char	**get_tokens(char *input, t_shell *shell)
{
	char	**tokens;

	tokens = tokenize_input(input, shell);
	if (!tokens)
		ft_error_msg(PARSER_ERR, "Failed to tokenize input");
	return (tokens);
}

/**
 * @brief Adds the user's input to the command history.
 * 
 * This function adds the given input string to the history using the readline
 * library. Input strings with a length of zero are ignored and not added.
 * 
 * @param input The user input string to be added to the history.
 * 
 * @note This function uses the `add_history` function from 
 * the readline library.
 */
static void	add_input_to_history(char *input)
{
	if (ft_strlen(input) > 0)
		add_history(input);
}

/**
 * @brief Processes a single command by building an abstract syntax tree (AST).
 * 
 * This function processes a single command by tokenizing it, parsing the tokens
 * to build an abstract syntax tree (AST), and then freeing the tokens array.
 * 
 * @param command The command string to be processed.
 * @param shell A pointer to the shell structure containing environment 
 * variables.
 * 
 * @note This function uses the `process_ast` function to build the AST.
 */
static void	process_single_command(char *command, t_shell *shell)
{
	t_ast	ast;
	char	**tokens;

	ast.root = NULL;
	tokens = get_tokens(command, shell);
	if (tokens)
	{
		process_ast(tokens, &ast, shell);
		free_tokens_array(tokens, -1);
	}
	free_ast(&ast);
	ast.root = NULL;
}

/**
 * @brief Processes the user's input by tokenizing and parsing it.
 * 
 * This function processes the user's input by tokenizing it into an array of
 * strings and then parsing the tokens to build an abstract syntax tree (AST).
 * If the input is empty, the function returns without processing it.
 * 
 * @param input The user input string to be processed.
 * @param shell A pointer to the shell structure containing environment 
 * variables.
 * 
 * @note This function uses the `process_ast` function to build the AST.
 */
static void	process_input(char *input, t_shell *shell)
{
	char	*command;
	char	*saveptr;
	char	*cmd_copy;

	command = ft_strtok_r(input, "\n", &saveptr);
	while (command)
	{
		if (ft_strlen(command) > 0)
		{
			cmd_copy = ft_strdup(command);
			if (!cmd_copy)
			{
				ft_error_msg("Error", "Memory allocation failed");
				return ;
			}
			process_single_command(cmd_copy, shell);
			safe_free((void **) &cmd_copy);
		}
		command = ft_strtok_r(NULL, "\n", &saveptr);
	}
}

/**
 * @brief Processes user input in the interactive shell.
 * 
 * This function reads user input using the readline library and processes it
 * by calling the `process_input` function. If the input is empty, the function
 * returns 0 to exit the shell. If the user sends a SIGINT signal, the function
 * returns 1 to continue the shell loop.
 * 
 * @param shell A pointer to the shell structure containing environment 
 * variables.
 * @return 1 if the shell loop should continue, 0 if the shell should exit.
 * 
 * @note This function uses the `readline` function from the readline library.
 * The input string is freed after use to prevent memory leaks.
 * 
 */
bool	receive_input(t_shell *shell)
{
	char			*input;
	t_syntax_error	error;

	input = readline("minishell$ ");
	if (!input)
		return (false);
	add_input_to_history(input);
	error = validate_input(input);
	if (error == SYNTAX_EMPTY)
	{
		safe_free((void **) &input);
		return (true);
	}
	else if (error != SYNTAX_OK)
	{
		handle_error(error, shell, NULL);
		safe_free((void **) &input);
		return (true);
	}
	process_input(input, shell);
	safe_free((void **) &input);
	return (true);
}
