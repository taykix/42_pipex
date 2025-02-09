/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:57:53 by tkarakay          #+#    #+#             */
/*   Updated: 2024/08/20 13:14:42 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdarg.h>

int	ft_is_arg_valid(char c)
{
	char	*valid_args;
	int		i;

	valid_args = "cspdiuxX%";
	i = 0;
	while (valid_args[i])
	{
		if (valid_args[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_args(va_list args, char arg, int *p_len)
{
	if (arg == 'c')
		ft_print_char_arg(args, p_len);
	else if (arg == 'd' || arg == 'i')
		ft_print_int_arg(args, p_len);
	else if (arg == '%')
	{
		ft_putchar('%');
		(*p_len)++;
	}
	else if (arg == 's')
		ft_print_str_arg(args, p_len);
	else if (arg == 'p')
		ft_print_ptr_arg(args, p_len);
	else if (arg == 'x')
		ft_print_hexl_arg(args, p_len);
	else if (arg == 'X')
		ft_print_hexb_arg(args, p_len);
	else if (arg == 'u')
		ft_print_u_arg(args, p_len);
}

int	ft_handle_percent(const char **p, va_list args, int *p_len)
{
	(*p)++;
	if (ft_is_arg_valid(**p))
		ft_print_args(args, **p, p_len);
	else
		ft_print_delim_arg(*p, p_len);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	const char	*p;
	int			p_len;

	p_len = 0;
	va_start(args, str);
	p = str;
	while (*p != '\0')
	{
		if (*p == '%')
		{
			ft_handle_percent(&p, args, &p_len);
		}
		else
		{
			ft_putchar(*p);
			p_len++;
		}
		p++;
	}
	va_end(args);
	return (p_len);
}
