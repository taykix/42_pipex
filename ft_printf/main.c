/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:29:47 by tkarakay          #+#    #+#             */
/*   Updated: 2024/08/20 13:12:08 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

/*
int	main(void)
{
	// FAILED TEST ON FRANCINETTE POINTERS
	printf("FAILED TEST ON FRANCINETTE POINTERS:\n");
	printf("Testing zero value:\n");
	printf("\nNumber of arguments on 0 ptr for ft_printf: %d, and for printf:
		%d \n", printf("%p", (void *)0), ft_printf("%p", 0));
	printf("\n+++++++++++++++++++++++++++++++++++++++\n");
	printf("\n+++++++++++++++++++++++++++++++++++++++\n");
	// Test Case 2: Zero value
	printf("printf, %x!\n", 0);
	ft_printf("ft_printf, %x!\n", 0);
	// Test Case 3: Small positive number
	printf("printf, %x!\n", 42);
	ft_printf("ft_printf, %x!\n", 42);
	// Test Case 4: Larger positive number
	printf("printf, %x!\n", 123456);
	ft_printf("ft_printf, %x!\n", 123456);
	// Test Case 5: Maximum unsigned int value
	printf("printf, %x!\n", 0xFFFFFFFF);
	ft_printf("ft_printf, %x!\n", 0xFFFFFFFF);
	// Test Case 6: Single digit hexadecimal
	printf("printf, %x!\n", 0xA);
	ft_printf("ft_printf, %x!\n", 0xA);
	// Test Case 7: Full byte value
	printf("printf, %x!\n", 0xFF);
	ft_printf("ft_printf, %x!\n", 0xFF);
	// Test Case 8: Multiple bytes (16 bits)
	printf("printf, %x!\n", 0xFFFF);
	ft_printf("ft_printf, %x!\n", 0xFFFF);
	// Test Case 9: Random hexadecimal value
	printf("printf, %x!\n", 0x123ABC);
	ft_printf("ft_printf, %x!\n", 0x123ABC);
	// Test Case 10: Hexadecimal with leading zeros
	printf("printf, %x!\n", 0x00000F);
	ft_printf("ft_printf, %x!\n", 0x00000F);
	// Test Case 11: every value (as unsigned int)
	printf(" %x %x %x %x %x %x %x \n", (unsigned int)INT_MAX,
		(unsigned int)INT_MIN, (unsigned int)LONG_MAX, (unsigned int)LONG_MIN,
		(unsigned int)ULONG_MAX, 0, (unsigned int)-42);
	ft_printf(" %x %x %x %x %x %x %x \n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN,
		ULONG_MAX, 0, -42);
	// Test Case 14: Negative larger number (as unsigned int)
	printf("printf, %x!\n", -42);
	ft_printf("ft_printf, %x!\n", -42);
	// HEX BIG TESTS
	printf("HEX BIG TESTS\n");
	printf("+++++++++++++++++++++++++++++++++++++++\n");
	// Test Case 2: Zero value
	printf("Testing zero value:\n");
	printf("printf, %X!\n", 0);
	ft_printf("ft_printf, %X!\n", 0);
	// Test Case 3: Small positive number
	printf("Testing small positive number:\n");
	printf("printf, %X!\n", 42);
	ft_printf("ft_printf, %X!\n", 42);
	// Test Case 4: Larger positive number
	printf("Testing larger positive number:\n");
	printf("printf, %X!\n", 123456);
	ft_printf("ft_printf, %X!\n", 123456);
	// Test Case 5: Maximum unsigned int value
	printf("Testing maximum unsigned int value:\n");
	printf("printf, %X!\n", 0xFFFFFFFF);
	ft_printf("ft_printf, %X!\n", 0xFFFFFFFF);
	// Test Case 6: Single digit hexadecimal
	printf("Testing single digit hexadecimal:\n");
	printf("printf, %X!\n", 0xA);
	ft_printf("ft_printf, %X!\n", 0xA);
	// Test Case 7: Full byte value
	printf("Testing full byte value:\n");
	printf("printf, %X!\n", 0xFF);
	ft_printf("ft_printf, %X!\n", 0xFF);
	// Test Case 8: Multiple bytes (16 bits)
	printf("Testing multiple bytes (16 bits):\n");
	printf("printf, %X!\n", 0xFFFF);
	ft_printf("ft_printf, %X!\n", 0xFFFF);
	// Test Case 9: Random hexadecimal value
	printf("Testing random hexadecimal value:\n");
	printf("printf, %X!\n", 0x123ABC);
	ft_printf("ft_printf, %X!\n", 0x123ABC);
	// Test Case 10: Hexadecimal with leading zeros
	printf("Testing hexadecimal with leading zeros:\n");
	printf("printf, %X!\n", 0x00000F);
	ft_printf("ft_printf, %X!\n", 0x00000F);
	// Test Case 11: Every value (as unsigned int)
	printf("Testing every value (as unsigned int):\n");
	printf(" %X %X %X %X %X %X %X \n", (unsigned int)INT_MAX,
		(unsigned int)INT_MIN, (unsigned int)LONG_MAX, (unsigned int)LONG_MIN,
		(unsigned int)ULONG_MAX, 0, (unsigned int)-42);
	ft_printf(" %X %X %X %X %X %X %X \n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN,
		ULONG_MAX, 0, -42);
	// Test Case 14: Negative larger number (as unsigned int)
	printf("Testing negative larger number (as unsigned int):\n");
	printf("printf, %X!\n", -42);
	ft_printf("ft_printf, %X!\n", -42);
	return (0);
}
*/
