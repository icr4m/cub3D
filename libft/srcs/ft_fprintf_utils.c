/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:23:59 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 20:04:01 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_r_type_fd(char c, va_list arg, int fd)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(arg, int), fd));
	if (c == 's')
		return (ft_putstr_fd_printf(va_arg(arg, char *), fd));
	if (c == 'p')
	{
		return (ft_p_fd(va_arg(arg, void *), fd));
	}
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(arg, int), fd));
	if (c == 'u')
		return (ft_print_nb_fd(va_arg(arg, int), fd));
	if (c == 'x')
		return (ft_putnbr_base_fd((unsigned int)(va_arg(arg, int)), HEXA_LOWER,
				fd));
	if (c == 'X')
		return (ft_putnbr_base_fd((unsigned int)(va_arg(arg, int)), HEXA_UPPER,
				fd));
	if (c == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}

size_t	ft_p_fd(void *ptr, int fd)
{
	if (ptr == NULL)
		return (ft_putstr_fd_printf("(nil)", fd));
	else
		return ((ft_putstr_fd_printf("0x", fd) + ft_putnbr_base((long)ptr,
					HEXA_LOWER)));
}
