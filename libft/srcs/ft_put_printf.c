/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:26:19 by ijaber            #+#    #+#             */
/*   Updated: 2024/07/03 15:37:36 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_putstr(char *str)
{
	size_t	print_len;

	print_len = 0;
	if (str == NULL)
		print_len += ft_putstr("(null)");
	else
	{
		while (*str != '\0')
		{
			print_len += ft_putchar(*str++);
		}
	}
	return (print_len);
}

size_t	ft_print_nb(unsigned int n)
{
	size_t	print_len;

	print_len = 0;
	if (n >= 10)
		print_len += ft_print_nb(n / 10);
	print_len += ft_putchar(n % 10 + '0');
	return (print_len);
}

size_t	ft_putnbr(long int n)
{
	size_t			print_len;
	unsigned int	num;

	print_len = 0;
	if (n < 0)
	{
		print_len += ft_putchar('-');
		num = -n;
	}
	else
		num = n;
	if (n == 0)
		print_len += ft_putchar('0');
	else
		print_len += ft_print_nb(num);
	return (print_len);
}

size_t	ft_putnbr_base(unsigned long nbr, char *base)
{
	const int	size_base = 16;
	int			nbr_final[100];
	int			i;
	size_t		print_len;

	print_len = 0;
	i = 0;
	if (nbr == 0)
		print_len += ft_putchar(base[0]);
	else
	{
		while (nbr)
		{
			nbr_final[i++] = nbr % size_base;
			nbr = nbr / size_base;
		}
		while (--i >= 0)
			print_len += ft_putchar(base[nbr_final[i]]);
	}
	return (print_len);
}
