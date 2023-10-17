#include "main.h"

/* PRINT POINTER */
/**
 * print_pointer - it Prints the value of a pointer variable
 * @types: it List a of arguments
 * @buffer: the Buffer array to handle print
 * @flags:  it Calculates active flags
 * @width: a get width
 * @precision: the Precision specification
 * @size: a Size specifier
 * Return: the Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/* PRINT NON PRINTABLE */
/**
 * print_non_printable - it Prints ascii codes in hexa of non printable chars
 * @types: it List a of arguments
 * @buffer: a Buffer array to handle print
 * @flags:  it Calculates active flags
 * @width: a get width
 * @precision: the Precision specification
 * @size: a Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int u = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[u] != '\0')
	{
		if (is_printable(str[u]))
			buffer[u + offset] = str[u];
		else
			offset += append_hexa_code(str[u], buffer, u + offset);

		u++;
	}

	buffer[u + offset] = '\0';

	return (write(1, buffer, u + offset));
}

/* PRINT REVERSE */
/**
 * print_reverse - to Prints reverse string.
 * @types: it List a of arguments
 * @buffer: a Buffer array to handle print
 * @flags:  to Calculates active flags
 * @width: a get width
 * @precision: a Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int o, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (o = 0; str[o]; o++)
		;

	for (o = o - 1; o >= 0; o--)
	{
		char z = str[o];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/* PRINT A STRING IN ROT13 */
/**
 * print_rot13string - to Print a string in rot13.
 * @types: to List a of arguments
 * @buffer: the Buffer array to handle print
 * @flags:  to Calculates active flags
 * @width: the get width
 * @precision: the Precision specification
 * @size: a Size specifier
 * Return: the Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int k, m;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (k = 0; str[k]; k++)
	{
		for (m = 0; in[m]; m++)
		{
			if (in[m] == str[k])
			{
				x = out[m];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[m])
		{
			x = str[k];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
