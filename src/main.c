/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:28:57 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/02 10:50:53 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point for the minishell program.
 * 
 * This file contains the main function that initializes the shell environment,
 * sets up signal handling, and starts the main execution loop. It also includes
 * functions for processing user input and managing the shell's state.
 * 
 * @note The code is designed to handle interactive shell sessions and
 * environment variable management. It uses a linked list structure to store
 * environment variables and provides functions for converting environment
 * variables to and from strings.
 */

#include "minishell.h"
#include "core/core.h"
#include "env/env.h"

bool	receive_input(t_shell *shell);
void	quit_shell(t_shell *shell);

/**
 * @brief Main loop of the shell.
 *
 * This function handles the main execution loop of the shell. It checks for
 * signals and processes user input. If a SIGINT signal is received, it clears
 * the signal and returns true to indicate that the shell should exit.
 *
 * @param shell A pointer to the shell structure containing environment
 * variables and exit status.
 * @return int Returns 0 upon successful termination.
 */
int	ft_main_loop(t_shell *shell)
{
	if (is_sigint_received())
	{
		clear_sigint();
		return (true);
	}
	while (1)
	{
		if (!receive_input(shell))
			break ;
	}
	quit_shell(shell);
	return (0);
}

/**
 * @brief Entry point for the minishell program.
 *
 * This function initializes the shell environment, sets up signal handling,
 * and starts the main execution loop. It ensures that environment variables
 * are properly converted into a linked list structure for internal use.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings (unused in this 
 * function).
 * @param envp An array of strings representing environment variables.
 * @return int Returns 0 upon successful termination.
 * 
 * @note If more than one argument is passed to the program, it exits
 * immediately with a failure status.
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	shell.env = env_to_linked_list(envp);
	if (!shell.env)
	{
		ft_error_msg("Error", "Failed to initialize environment");
		exit(EXIT_FAILURE);
	}
	shell.exit_status = 0;
	setup_interactive_signals();
	ft_main_loop(&shell);
	return (0);
}
