/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:31:57 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 15:32:38 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static bool	ft_isoverflowing(long number, long sign, char c)
{
	if (number > (LONG_MAX - (c - '0')) / 10)
		return (1);
	if ((number * sign) < INT_MIN || (number * sign) > INT_MAX)
		return (1);
	return (0);
}

int	ft_atol_safe(long *dest, const char *string)
{
	size_t	index;
	long	sign;
	long	number;

	index = 0;
	sign = 1;
	number = 0;
	while (is_whitespace(string[index]))
		index++;
	if (string[index] == '+' || string[index] == '-')
	{
		if (string[index] == '-')
			sign *= -1;
		index++;
	}
	while (ft_isdigit(string[index]))
	{
		number *= 10;
		number += string[index] - '0';
		if (ft_isoverflowing(number, sign, string[index]) == 1)
			return (0);
		index++;
	}
	*dest = sign * number;
	return (1);
}
