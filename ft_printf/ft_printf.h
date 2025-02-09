/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:21:50 by tayki             #+#    #+#             */
/*   Updated: 2024/08/20 13:14:40 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

int		ft_is_arg_valid(char c);
void	ft_print_char_arg(va_list args, int *p_len);
void	ft_print_str_arg(va_list args, int *p_len);
void	ft_print_int_arg(va_list args, int *p_len);
void	ft_print_delim_arg(const char *p, int *p_len);
void	ft_print_char(const char *p, int *p_len);
void	ft_print_args(va_list args, char arg, int *p_len);
void	ft_print_ptr_arg(va_list args, int *plen);
void	ft_print_hexb_arg(va_list args, int *p_len);
void	ft_print_hexl_arg(va_list args, int *p_len);
void	ft_print_u_arg(va_list args, int *p_len);
int		ft_printf(const char *str, ...);
int		ft_handle_percent(const char **p, va_list args, int *p_len);

#endif
