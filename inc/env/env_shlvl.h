/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:44:23 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:19:47 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_shlvl.h
 * @brief This file contains the function prototypes for managing the SHLVL
 * environment variable in the shell.
 */

#include "minishell.h"

void	initialize_shlvl(t_env **env);
void	increment_shlvl(t_env **env);
void	reset_shlvl(t_env **env);