/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:26:04 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/03/24 18:43:03 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/str_utils.h"

void	*safe_malloc(size_t size);
size_t	ft_strlen(const char *s);

char	*ft_strcpy(char *dest, const char *src)
{
	char	*temp;

	temp = dest;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (temp);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	char		*start;

	if (str)
		s = str;
	if (!s)
		return (NULL);
	while (*s && ft_strchr(delim, *s))
		s++;
	if (!*s)
		return (NULL);
	start = s;
	while (*s && !ft_strchr(delim, *s))
		s++;
	if (*s)
	{
		*s = '\0';
		s++;
	}
	return (start);
}

/**
 * @brief Compares two strings.
 *
 * This function compares the two strings s1 and s2. It returns an integer
 * less than, equal to, or greater than zero if s1 is found, respectively,
 * to be less than, to match, or be greater than s2.
 * Handles NULL inputs safely.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return int An integer indicating the result of the comparison.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (-1);
	if (s2 == NULL)
		return (1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * @brief Fills the given string with the integer value.
 *
 * This static function takes a string pointer, an integer, and the length
 * of the string. It fills the string with the integer value, converting
 * the integer to its string representation.
 *
 * @param str Pointer to the string to be filled.
 * @param n Integer value to be converted and placed into the string.
 * @param len Length of the string.
 */
void	fill_str(char *str, int n, size_t len)
{
	int		is_negative;
	size_t	i;
	int		digit;

	is_negative = n < 0;
	i = len - 1;
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		digit = n % 10;
		if (is_negative)
			digit *= -1;
		str[i--] = digit + '0';
		n /= 10;
	}
	if (is_negative)
		str[0] = '-';
}

/**
 * @brief Duplicates a string.
 *
 * This function allocates sufficient memory for a copy of the string s,
 * does the copy, and returns a pointer to it. The memory allocated for
 * the new string should be freed by the caller when it is no longer needed.
 *
 * @param s The string to be duplicated.
 * @return A pointer to the newly allocated string, or NULL if memory
 * allocation fails.
 */
char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dup = safe_malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, src);
	return (dup);
}
