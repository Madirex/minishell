/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:42:26 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/21 16:24:20 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file unset_cmd.h
 * @brief Unset command header file.
 *
 * This file contains the declarations of functions and structures used for
 * handling the unset command in a shell environment. The unset command is used
 * to remove environment variables from the shell's environment.
 */

#ifndef UNSET_CMD_H
# define UNSET_CMD_H

# include "env/env.h"
# include "types.h"
# include "utils/str_utils.h"

void	handle_unset(char **args, t_shell *shell);

#endif
