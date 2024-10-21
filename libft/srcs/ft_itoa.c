/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:55:14 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/24 14:24:17 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Donne la valeur absolue
static unsigned int	get_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static size_t	nb_len(int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static void	fill_number(char *src, int nb, unsigned int len)
{
	unsigned int	i;
	unsigned int	n_abs;

	i = 0;
	n_abs = get_abs(nb);
	while (i < len)
	{
		src[len - i - 1] = (n_abs % 10) + '0';
		n_abs /= 10;
		i++;
	}
	src[len] = '\0';
}

char	*ft_itoa(int n)
{
	char	*new;
	int		len;
	bool	is_neg;

	if (n == 0)
		return (ft_strdup("0"));
	is_neg = (n < 0);
	len = nb_len(n);
	new = (char *)gc_malloc((len + is_neg) * sizeof(char) + 1);
	if (!new)
		return (NULL);
	if (is_neg)
		new[0] = '-';
	fill_number(new + is_neg, n, len);
	return (new);
}
/*
int	main(void)
{
	printf("string :%s\n", ft_itoa(INT32_MIN));
	printf("string :%s\n", ft_itoa(INT32_MAX));
	printf("string :%s\n", ft_itoa(-123));
	printf("string :%s\n", ft_itoa(2));
	printf("string :%s\n", ft_itoa(0));
	printf("string :%s\n", ft_itoa(123));
	return (0);
}
*/
