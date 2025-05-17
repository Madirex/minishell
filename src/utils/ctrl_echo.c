/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:09:26 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/05 13:40:30 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ctrl_echo.c
 * 
 * Functions for enabling and disabling echoing of control characters 
 * in the terminal.
 * 
 */
#include "signals/signals.h"

/**
 * @brief Disables echoing of control characters in the terminal.
 * 
 * This function disables echoing of control characters in the terminal
 * by modifying the terminal attributes to ignore control characters.
 * This is useful for handling signals like SIGINT and SIGQUIT in the
 * context of interactive shell input.
 * 
 */
void	disable_ctrl_echo(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == 0)
	{
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
}

/**
 * @brief Enables echoing of control characters in the terminal.
 * 
 * This function enables echoing of control characters in the terminal
 * by modifying the terminal attributes to include control characters.
 * This is useful for restoring the default terminal behavior after
 * handling signals like SIGINT and SIGQUIT in the context of interactive
 * shell input.
 */
void	enable_ctrl_echo(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == 0)
	{
		t.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
}
