/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:42:10 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/21 16:28:20 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_cmd.h
 * @brief Environment command header file.
 * 
 * This file contains the declarations of functions and structures used for
 * handling the env command in a shell environment. The env command is used
 * to display the current environment variables and their values.
 * It can also be used to set environment variables for a command.
 */

#ifndef ENV_CMD_H
# define ENV_CMD_H

# include "env/env.h"
# include "utils/str_utils.h"
# include "types.h"
# include "ast/ast.h"

void	handle_env(t_ast_node *node, t_env *env);

#endif
