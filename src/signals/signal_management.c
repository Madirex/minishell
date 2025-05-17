/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:09:50 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/14 13:23:14 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signal_management.c
 * 
 * @brief Signal management utilities for minishell
 * 
 * This file contains functions for blocking and unblocking signals in the
 * minishell program. These utilities ensure that the shell can handle
 * signals appropriately during critical sections of code execution.
 * 
 * ### Key Features:
 * - Blocking and unblocking signals.
 * - Checking for received signals (e.g., SIGINT).
 * - Resetting the signal state after processing signals.
 * - Ensuring signal-safe operations in the shell program.
 * 
 * @see signals.h
 */

#include "signals/signals.h"

/**
 * @brief Blocks all signals.
 *
 * This function is used to block all signals in the current process.
 * It is  used to prevent the process from being interrupted
 * by signals during critical sections of code.
 */
void	block_signals(void)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sigprocmask(MS_SIG_BLOCK, &mask, NULL);
}

/**
 * @brief Unblocks signals that were previously blocked.
 *
 * This function is responsible for unblocking signals that may have been
 * blocked during the execution of the program. It ensures that the signals
 * are properly handled and the program can respond to them as expected.
 */
void	unblock_signals(void)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sigprocmask(MS_SIG_UNBLOCK, &mask, NULL);
}

/**
 * @brief Checks if a SIGINT signal has been received.
 *
 * This function checks the `g_signal_state` variable to determine if a
 * SIGINT signal (e.g., Ctrl+C) has been received. It allows the program
 * to respond appropriately to interruptions, such as redisplaying the prompt
 * or exiting heredoc mode.
 *
 * @return true if a SIGINT signal has been received, false otherwise.
 *
 * @note After detecting a received SIGINT, call `clear_sigint` to reset
 * the signal state and avoid repeated processing of the same signal.
 */
bool	is_sigint_received(void)
{
	return ((g_signal_state & SIG_INT) != 0);
}

/**
 * @brief Clears the SIGINT signal state.
 *
 * This function resets the `SIG_INT` bit in the global `g_signal_state`
 * variable, indicating that the program has handled the interrupt signal.
 *
 * @note This function should be called after processing a SIGINT to 
 * ensure the program does not repeatedly process the same signal.
 */
void	clear_sigint(void)
{
	g_signal_state &= ~SIG_INT;
}
