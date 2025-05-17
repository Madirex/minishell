/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:00:16 by ybolivar          #+#    #+#             */
/*   Updated: 2025/03/05 13:09:05 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signal_handlers.c
 * @brief Signal handling utilities for minishell
 *
 * This file contains functions and a global variable for managing and 
 * handling signals in the minishell program. These utilities ensure
 * appropriate responses to user-triggered signals, such as SIGINT 
 * (Ctrl+C), across different shell contexts.
 */

#include "signals/signals.h"

/**
 * @brief Signal handler for SIGINT during heredoc.
 * 
 * This function handles the SIGINT signal (Ctrl+C) during heredoc
 * input. It writes a newline to `STDERR_FILENO` and closes the
 * standard input file descriptor to terminate the heredoc process.
 * 
 * ### Key Operations:
 * - Writes a newline to `STDERR_FILENO` for prompt clarity.
 * - Closes the standard input file descriptor to terminate heredoc.
 * 
 * @param sig The signal number (expected to be SIGINT).
 * 
 * ### Note:
 * - This function is used in the heredoc context to handle user
 *   interruptions gracefully.
 */
void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

/**
 * @brief Resets signal handlers to their default behavior.
 *
 * This function restores the default signal handlers for SIGINT and
 * SIGQUIT. It also resets the global signal state to `SIG_NONE` to
 * indicate that no signals are currently active.
 */
void	reset_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	g_signal_state = SIG_NONE;
}

/**
 * @brief Signal handler for SIGINT during interactive mode.
 *
 * This function handles SIGINT signals (Ctrl+C) in interactive mode.
 * It updates the global signal state and reconfigures the readline 
 * state to redisplay the shell prompt without exiting.
 *
 * ### Key Operations:
 * - Updates `g_signal_state` to indicate SIGINT was received.
 * - Writes a newline to `STDERR_FILENO` for prompt clarity.
 * - Clears the current readline input and redisplays the prompt.
 *
 * @param sig The signal number (expected to be SIGINT).
 * 
 * ### Note:
 * - This function is used in interactive mode to handle user
 *   interruptions gracefully without terminating the shell.
 * - It ensures that the readline library is properly updated to
 *   reflect the new state of the shell after a signal is received.
 * - The `errno` variable is preserved across the signal handler
 *   execution
 */
void	handle_sigint(int sig)
{
	int	saved_errno;

	saved_errno = errno;
	(void)sig;
	g_signal_state |= SIG_INT;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	errno = saved_errno;
}

/**
 * @brief Signal handler for SIGINT during command execution.
 *
 * This function handles SIGINT signals (Ctrl+C) during command execution.
 * It simply prints a newline character to ensure proper formatting when
 * a command is interrupted.
 *
 * @param sig The signal number (expected to be SIGINT).
 */
void	handle_sigint_during_execution(int sig)
{
	(void)sig;
	g_signal_state |= SIG_INT;
	write(STDERR_FILENO, "\n", 1);
}
