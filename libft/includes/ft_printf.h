/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:07:45 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 20:00:21 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define HEXA_LOWER "0123456789abcdef"
# define HEXA_UPPER "0123456789ABCDEF"

int		ft_printf(char const *str, ...);
size_t	ft_putchar(char c);
size_t	ft_putstr(char *str);
size_t	ft_putnbr(long int n);
size_t	ft_r_type(char c, va_list arg);
size_t	ft_putnbr_base(unsigned long nbr, char *base);
size_t	ft_print_nb(unsigned int n);
size_t	ft_p(void *ptr);

// FPRINTF
int		ft_fprintf(int fd, char const *str, ...);

size_t	ft_putchar_fd(char c, int fd);
size_t	ft_putstr_fd_printf(char *str, int fd);
size_t	ft_print_nb_fd(unsigned int n, int fd);
size_t	ft_putnbr_fd(long int n, int fd);
size_t	ft_putnbr_base_fd(unsigned long nbr, char *base, int fd);

size_t	ft_r_type_fd(char c, va_list arg, int fd);
size_t	ft_p_fd(void *ptr, int fd);

#endif
