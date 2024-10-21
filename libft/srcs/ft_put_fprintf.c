/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fprintf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:38:22 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 20:04:33 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

size_t	ft_putstr_fd_printf(char *str, int fd)
{
	size_t	print_len;

	print_len = 0;
	if (str == NULL)
		print_len += ft_putstr_fd_printf("(null)", fd);
	else
	{
		while (*str != '\0')
		{
			print_len += ft_putchar_fd(*str++, fd);
		}
	}
	return (print_len);
}

size_t	ft_print_nb_fd(unsigned int n, int fd)
{
	size_t	print_len;

	print_len = 0;
	if (n >= 10)
		print_len += ft_print_nb_fd(n / 10, fd);
	print_len += ft_putchar_fd(n % 10 + '0', fd);
	return (print_len);
}

size_t	ft_putnbr_fd(long int n, int fd)
{
	size_t			print_len;
	unsigned int	num;

	print_len = 0;
	if (n < 0)
	{
		print_len += ft_putchar_fd('-', fd);
		num = -n;
	}
	else
		num = n;
	if (n == 0)
		print_len += ft_putchar_fd('0', fd);
	else
		print_len += ft_print_nb_fd(num, fd);
	return (print_len);
}

size_t	ft_putnbr_base_fd(unsigned long nbr, char *base, int fd)
{
	const int	size_base = 16;
	int			nbr_final[100];
	int			i;
	size_t		print_len;

	print_len = 0;
	i = 0;
	if (nbr == 0)
		print_len += ft_putchar_fd(base[0], fd);
	else
	{
		while (nbr)
		{
			nbr_final[i++] = nbr % size_base;
			nbr = nbr / size_base;
		}
		while (--i >= 0)
			print_len += ft_putchar_fd(base[nbr_final[i]], fd);
	}
	return (print_len);
}
