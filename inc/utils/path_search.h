/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:24:35 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:54:32 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file path_search.h
 * @brief This file contains the function to search for a command in the PATH.
 */

#ifndef PATH_SEARCH_H
# define PATH_SEARCH_H

# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <stdio.h>
# include "types.h"

char	*search_in_path(const char *cmd, t_env *env);

#endif