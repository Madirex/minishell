/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:41:08 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/01/08 10:35:23 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/char_utils.h"

/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function returns true if the character c is a whitespace character
 * (space, tab, newline, vertical tab, form feed, or carriage return).
 *
 * @param c The character to check.
 * @return bool True if the character is a whitespace character, false if not.
 */
bool	ft_isspace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

/**
 * @brief Checks if a character is alphanumeric.
 *
 * This function returns true if the character c is an alphanumeric character
 * (either a digit or a letter).
 *
 * @param c The character to check.
 * @return bool True if the character is alphanumeric, false otherwise.
 */
bool	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

/**
 * @brief Checks if a character is a digit.
 *
 * This function returns true if the character c is a digit (0-9).
 *
 * @param c The character to check.
 * @return bool True if the character is a digit, false otherwise.
 */
bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Checks if the character is an alphabetic letter.
 *
 * @param c The character to check.
 * @return 1 if the character is alphabetic, 0 otherwise.
 */
bool	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/**
* @brief Checks if a character is a delimiter.
* @param c The character to be checked.
* @param delim A string containing delimiter characters.
* @return true if the character is a delimiter, false otherwise.
*/
bool	is_delimiter(const char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (true);
		delim++;
	}
	return (false);
}
