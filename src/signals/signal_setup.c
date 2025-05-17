/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:11:27 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/01/19 13:24:29 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signal_setup.c
 * @brief Signal setup utilities for minishell
 *
 * This file provides functions for configuring signal handlers in different
 * contexts of the minishell program. These utilities ensure appropriate
 * behavior for interactive prompts, heredoc inputs, and other situations
 * where signal handling is required.
 *
 * ### Key Features:
 * - Context-specific signal setups:
 *   - Interactive prompt signals.
 *   - Heredoc-specific signals.
 * - Signal-safe updates to global signal state (`g_signal_state`).
 * - Ignoring irrelevant signals (e.g., SIGQUIT in the shell prompt).
 */

#include "signals/signals.h"

/**
 * @brief Global variable for managing signal states.
 *
 * This variable uses bitwise flags to track different signal states
 * (e.g., SIGINT). It is declared as `volatile sig_atomic_t` to ensure
 * that updates to its value are atomic and remain consistent in the
 * presence of signal interruptions.
 *
 * @note This variable should only be modified or read using signal-safe
 * operations to avoid undefined behavior.
 */
volatile sig_atomic_t	g_signal_state = SIG_NONE;

/**
 * @brief Sets a custom signal handler for a given signal.
 *
 * This function configures a signal handler for a specific signal number 
 * using `sigaction`. The handler is applied with the `SA_RESTART` flag to 
 * ensure interrupted system calls are restarted automatically.
 *
 * @param signum The signal number to handle (e.g., SIGINT, SIGQUIT).
 * @param handler A pointer to the signal handler function to invoke when 
 * the signal is received.
 *
 * @note If `sigaction` fails, the function prints an error message 
 * and exits the program.
 */
void	set_signal_handler(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Configures signal handlers for heredoc input.
 *
 * This function sets up signal handlers specifically for handling signals
 * during heredoc input. It ensures that:
 * - **SIGINT (Ctrl+C):** Invokes `sigint_heredoc_handler` to gracefully exit
 *   heredoc input without corrupting the terminal state.
 * - **SIGQUIT (Ctrl+\):** Is ignored to prevent unintended shell termination.
 */
void	setup_signals_for_heredoc(void)
{
	set_signal_handler(SIGINT, sigint_heredoc_handler);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

/**
 * @brief Configures signal handlers for interactive prompts.
 *
 * This function sets up signal handlers for the interactive shell prompt.
 * It ensures that:
 * - **SIGINT (Ctrl+C):** Invokes `handle_sigint` to clear the current input
 *   and redisplay the prompt without exiting the shell.
 * - **SIGQUIT (Ctrl+\):** Is ignored to prevent unintended shell termination.
 *
 * The global signal state (`g_signal_state`) is also reset to `SIG_NONE`.
 */
void	setup_interactive_signals(void)
{
	set_signal_handler(SIGINT, handle_sigint);
	set_signal_handler(SIGQUIT, SIG_IGN);
	g_signal_state = SIG_NONE;
}

/**
 * @brief Configures signal handlers for command execution.
 *
 * This function sets up signal handlers specifically for when the shell is
 * executing external commands. It restores default behavior for signals so
 * that they affect the child processes but not the parent shell.
 */
void	setup_signals_for_execution(void)
{
	set_signal_handler(SIGINT, SIG_DFL);
	set_signal_handler(SIGQUIT, SIG_DFL);
	g_signal_state = SIG_NONE;
}
