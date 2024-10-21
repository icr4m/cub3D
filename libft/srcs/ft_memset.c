/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:10:07 by ijaber            #+#    #+#             */
/*   Updated: 2024/03/23 18:01:41 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)b;
	while (len)
	{
		*tmp = (unsigned char)c;
		tmp++;
		len--;
	}
	return (b);
}

/*
int	main(void)
{
	char	str[20] = "Hello, World!";
	char	str2[20] = "Hello, World!";

	// Using custom ft_memset function
	ft_memset(str, 'a', 5);
	printf("Custom ft_memset result: %s\n", str);
	// Using standard memset function
	memset(str2, 'a', 5);
	printf("Standard memset result: %s\n", str2);
	return (0);
}
*/
