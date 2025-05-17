/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:42:00 by anmateo-          #+#    #+#             */
/*   Updated: 2025/04/21 16:14:22 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cd_cmd.h
 * @brief Header file for the cd command implementation.
 * 
 * This file contains the function declarations and includes necessary for
 * implementing the cd command in a shell environment. The cd command is used
 * to change the current working directory of the shell.
 */

#ifndef CD_CMD_H
# define CD_CMD_H

# include "utils/str_utils.h"
# include "utils/mem_utils.h"
# include "builtins/pwd_cmd.h"
# include "env/env.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

void	handle_cd(char **args, t_shell *shell);
char	*handle_oldpwd(t_env *env);
char	*get_cd_path(char **args, t_env *env, bool *free_dir);
char	*get_absolute_path(char *path, char *arg, bool *free_dir);

#endif
