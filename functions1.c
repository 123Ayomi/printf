#include "main.h"

/* PRINT UNSIGNED NUMBER */
/**
 * print_unsigned - it Prints an unsigned number
 * @types: it List a of arguments
 * @buffer: a Buffer array to handle print
 * @flags:  the Calculates active flags
 * @width: a get width
 * @precision: the Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = (num % 10) + '0';
		num /= 10;
	}

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN OCTAL  */
/**
 * print_octal - it Prints an unsigned number in octal notation
 * @types: it List a of arguments
 * @buffer: the Buffer array to handle print
 * @flags:  it Calculates active flags
 * @width: a get width
 * @precision: a Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[k--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[k--] = '0';

	k++;

	return (write_unsgnd(0, k, buffer, flags, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN HEXADECIMAL */
/**
 * print_hexadecimal - it Prints an unsigned number in hexadecimal notation
 * @types: it List a of arguments
 * @buffer: a Buffer array to handle print
 * @flags: it Calculates active flags
 * @width: a get width
 * @precision: the Precision specification
 * @size: a Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL */
/**
 * print_hexa_upper - it Prints an unsigned num in upper hex notation
 * @types: it List a of arguments
 * @buffer: a Buffer array to handle print
 * @flags:  it Calculates active flags
 * @width: a get width
 * @precision: a Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/* PRINT HEXX NUM IN LOWER OR UPPER */
/**
 * print_hexa - it Prints a hexadecimal number in lower or upper
 * @types: it List a of arguments
 * @map_to: the Array of values to map the number to
 * @buffer: the Buffer array to handle print
 * @flags:  it Calculates active flags
 * @flag_ch: it Calculates active flags
 * @width: a get width
 * @precision: the  Precision specification
 * @size: a Size specifier
 * @size: a Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[y--] = flag_ch;
		buffer[y--] = '0';
	}

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}
