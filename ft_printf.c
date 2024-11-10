/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos <msantos@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:04:14 by msantos           #+#    #+#             */
/*   Updated: 2024/11/10 18:01:30 by msantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write (1, &c, 1));
}

static int	istypevalid(char c)
{
	char	*types;

	types = "cspdiuxX%";
	while (*types)
	{
		if (c == *types)
			return (1);
		types++;
	}
	return (0);
}

static int	print_type(va_list *args, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar(va_arg(*args, int));
	else if (c == '%')
		count = ft_putchar('%');
	else if (c == 's')
		count = ft_putstr(va_arg(*args, char *));
	else if (c == 'i' || c == 'd')
		count = ft_putnbr(va_arg(*args, int));
	else if (c == 'u')
		count = ft_putnbr(va_arg(*args, unsigned int));
	else if (c == 'x')
		count = ft_putnbr_hexa(va_arg(*args, unsigned int), 0);
	else if (c == 'X')
		count = ft_putnbr_hexa(va_arg(*args, unsigned int), -32);
	else if (c == 'p')
		count = ft_ptr(va_arg(*args, unsigned long long));
	return (count);
}

int	ft_printf(const char *type, ...)
{
	size_t	i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, type);
	while (type[i])
	{
		if (type[i] == '%' && type[i + 1] && istypevalid(type[i + 1]))
			count += print_type(&args, type[++i]);
		else
			count += ft_putchar(type[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
#include "stddef.h"

int main(void)
{
    int real_return, my_return;

    // Test with strings
    real_return = printf("Real: %s\n", "Hello, World!");
    my_return = ft_printf("Mine: %s\n", "Hello, World!");
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Test with NULL string
    real_return = printf("Real: %s\n", (char *)NULL);
    my_return = ft_printf("Mine: %s\n", (char *)NULL);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Test with characters
    real_return = printf("Real: %c\n", 'A');
    my_return = ft_printf("Mine: %c\n", 'A');
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Test with integers
    real_return = printf("Real: %d\n", 12345);
    my_return = ft_printf("Mine: %d\n", 12345);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Test with unsigned integers
    real_return = printf("Real: %u\n", 12345);
    my_return = ft_printf("Mine: %u\n", 12345);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Test with hexadecimal (lowercase)
    real_return = printf("Real: %x\n", 12345);
    my_return = ft_printf("Mine: %x\n", 12345);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Additional tests for %x (lowercase)
    real_return = printf("Real: %x\n", 0);
    my_return = ft_printf("Mine: %x\n", 0);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    real_return = printf("Real: %x\n", 255);
    my_return = ft_printf("Mine: %x\n", 255);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    real_return = printf("Real: %x\n", 4294967295U);
    my_return = ft_printf("Mine: %x\n", 4294967295U);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Test with hexadecimal (uppercase)
    real_return = printf("Real: %X\n", 12345);
    my_return = ft_printf("Mine: %X\n", 12345);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Additional tests for %X (uppercase)
    real_return = printf("Real: %X\n", 0);
    my_return = ft_printf("Mine: %X\n", 0);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    real_return = printf("Real: %X\n", 255);
    my_return = ft_printf("Mine: %X\n", 255);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    real_return = printf("Real: %X\n", 4294967295U);
    my_return = ft_printf("Mine: %X\n", 4294967295U);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Test with pointer
    int x = 42;
    real_return = printf("Real: %p\n", (void *)&x);
    my_return = ft_printf("Mine: %p\n", (void *)&x);
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    // Test with percentage
    real_return = printf("Real: %%\n");
    my_return = ft_printf("Mine: %%\n");
    printf("Real return: %d | Mine return: %d\n\n", real_return, my_return);

    return 0;
}*/
