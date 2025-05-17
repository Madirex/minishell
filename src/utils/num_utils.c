/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:43:39 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/02/09 19:43:28 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/num_utils.h"

void	*safe_malloc(size_t size);

/**
 * @brief Calculates the length of the number when represented as a string.
 *
 * This function takes an integer as input and returns the number of characters
 * required to represent that integer as a string, including the sign if the
 * number is negative.
 *
 * @param n The integer whose length is to be calculated.
 * @return The length of the integer when represented as a string.
 */
static size_t	get_num_len(int n)
{
	size_t	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/**
 * @file ft_atoi.c
 * @brief Converts a string to an integer.
 *
 * This function takes a string as input and converts it to an integer.
 * It handles optional leading whitespace and an optional sign.
 *
 * @param str The string to be converted to an integer.
 * @return The integer value of the string.
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	val;

	val = 0;
	sign = 1;
	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = (val * 10) + (str[i] - '0');
		i++;
	}
	return (val * sign);
}

/**
 * @brief Converts an integer to a null-terminated string.
 *
 * This function takes an integer value and converts it to a string
 * representation. The resulting string is dynamically allocated and
 * must be freed by the caller.
 *
 * @param n The integer to be converted.
 * @return A pointer to the newly allocated string representing the integer.
 */
char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = get_num_len(n);
	str = safe_malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	fill_str(str, n, len);
	return (str);
}
