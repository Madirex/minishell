/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:28:57 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:45:15 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file core.h
 * @brief This file contains the core functions of the shell.
 */

#ifndef CORE_H
# define CORE_H
# include "types.h"
# include "minishell.h"

bool	receive_input(t_shell *shell);

#endif
