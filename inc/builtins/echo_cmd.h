/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:42:04 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/21 16:22:38 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @file echo_cmd.h
* @brief Echo command header file.
* 
* This file contains the declarations of functions and structures used for
* handling the echo command in a shell environment. The echo command is used
* to display a line of text or a variable value to the standard output.
*/

#ifndef ECHO_CMD_H
# define ECHO_CMD_H

# include "ast/ast.h"
# include "types.h"
# include "utils/str_utils.h"
# include <unistd.h>

void	handle_echo(t_ast_node *node, t_shell *shell);

#endif
