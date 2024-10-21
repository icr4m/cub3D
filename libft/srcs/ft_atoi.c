/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:16:09 by ijaber            #+#    #+#             */
/*   Updated: 2024/05/17 14:50:54 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *string)
{
	int	sign;
	int	number;

	sign = 1;
	while (is_whitespace(*string))
		string++;
	if (*string == '-')
	{
		sign = -1;
		string++;
	}
	else if (*string == '+')
		string++;
	number = 0;
	while (*string != '\0' && (*string >= '0' && *string <= '9'))
	{
		number = number * 10 + *string - '0';
		string++;
	}
	return (number * sign);
}

/*
int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("The value of the homemade atoi is :%d\n", ft_atoi(av[1]));
		printf("The value of the real atoi is :%d", atoi(av[1]));
	}
}
*/
