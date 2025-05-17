/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:49:00 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:50:26 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signals.h
 * @brief This file contains the definitions of signal handling functions.
 * 
 * This file includes the definitions of functions for setting up
 * signal handlers, handling signals, and managing signal states.
 * It also includes the definition of the global variable g_signal_state,
 * which is used to keep track of the current signal state, and the masks
 * for blocking and unblocking signals.
 * Masks include:
 * - MS_SIG_BLOCK: Block signals.
 * - MS_SIG_UNBLOCK: Unblock signals.
 * - MS_SIG_SETMASK: Set signal mask.
 */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <sys/ioctl.h>
# include <sys/errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <termios.h>
# include "types.h"

# define MS_SIG_BLOCK    0
# define MS_SIG_UNBLOCK  1
# define MS_SIG_SETMASK  2

// Global variable
extern volatile sig_atomic_t	g_signal_state;

/* Signal setup.c */
void	setup_interactive_signals(void);
void	setup_heredoc_signals(void);

/* Signal handling */
void	rl_replace_line(const char *text, int clear_undo);
void	handle_sigint(int sig);
bool	is_sigint_received(void);
void	clear_sigint(void);
void	sigint_heredoc_handler(int sig);

/* Signal management */
void	block_signals(void);
void	unblock_signals(void);
void	reset_signal_handlers(void);

#endif
