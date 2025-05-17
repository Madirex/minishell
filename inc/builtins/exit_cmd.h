/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:32:20 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 16:29:29 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exit_cmd.h
 * @brief Exit command header file.
 * 
 * This file contains the declarations of functions and structures used for
 * handling the exit command in a shell environment. The exit command is used
 * to terminate the shell session and return an exit status to the operating
 * system.
 */

#ifndef EXIT_CMD_H
# define EXIT_CMD_H

# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include "types.h"

void	handle_exit(char **args, t_shell *shell);

#endif
