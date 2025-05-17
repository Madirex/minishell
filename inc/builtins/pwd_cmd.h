/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:42:21 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/21 16:28:03 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd_cmd.h
 * @brief PWD command header file.
 * 
 * This file contains the declarations of functions and structures used for
 * handling the PWD command in a shell environment. The PWD command is used
 * to print the current working directory.
 */

#ifndef PWD_CMD_H
# define PWD_CMD_H

# include "utils/str_utils.h"
# include "types.h"
# include "ast/ast.h"
# include <unistd.h>

char	*get_current_directory(void);
void	handle_pwd(t_ast_node *node);

#endif
