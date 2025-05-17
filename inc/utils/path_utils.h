/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:48:40 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:56:38 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file path_utils.h
 * @brief This file contains the function to resolve a command's full path.
 *
 * This file includes the definition of the function that resolves a command's
 * full path by searching in the PATH environment variable.
 * It also includes one ifdef directive to include the sys/syslimits.h header
 * file on macOS systems, which defines the PATH_MAX constant.
 * The PATH_MAX constant is defined to be 4096 bytes if it is not already
 * defined. This is to ensure that the code is portable across different systems.
 */

#ifndef PATH_UTILS_H
# define PATH_UTILS_H

# include <limits.h>
# ifdef __APPLE__
#  include <sys/syslimits.h>
# endif
# include <sys/types.h>
# include <sys/stat.h>
# include "types.h"
# include "path_search.h"

# ifndef PATH_MAX
#  ifdef MAXPATHLEN
#   define PATH_MAX MAXPATHLEN
#  else
#   define PATH_MAX 4096
#  endif
# endif

char	*resolve_command(const char *cmd, t_env *env);

#endif
