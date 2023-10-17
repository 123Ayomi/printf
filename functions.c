#include "main.h"

/* PRINT CHAR */

/**
* print_char - it Prints a char
* @types: it List a of arguments
* @buffer: a Buffer array to handle print
* @flags:  it Calculates active flags
* @width: a Width
* @precision: the Precision specification
* @size: a Size specifier
* Return: the Number of chars printed
*/
int print_char(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
char c = va_arg(types, int);

return (handle_write_char(c, buffer, flags, width, precision, size));
}

/* PRINT A STRING */

/**
* print_string - it Prints a string
* @types: it List a of arguments
* @buffer: a Buffer array to handle print
* @flags:  it Calculates active flags
* @width: a get width.
* @precision: the Precision specification
* @size: a Size specifier
* Return: the Number of chars printed
*/
int print_string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int length = 0, p;
char *str = va_arg(types, char *);

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
if (str == NULL)
{
str = "(null)";
if (precision >= 6)
str = "      ";
}

while (str[length] != '\0')
length++;

if (precision >= 0 && precision < length)
length = precision;

if (width > length)
{
if (flags & F_MINUS)
{
write(1, &str[0], length);
for (p = width - length; p > 0; p--)
write(1, " ", 1);
return (width);
}
else
{
for (p = width - length; p > 0; p--)
write(1, " ", 1);
write(1, &str[0], length);
return (width);
}
}

return (write(1, str, length));
}
/* PRINT PERCENT SIGN */
/**
* print_percent - it Prints a percent sign
* @types: it List a of arguments
* @buffer: a Buffer array to handle print
* @flags:  it Calculates active flags
* @width: a get width.
* @precision: the Precision specification
* @size: a Size specifier
* Return: a Number of chars printed
*/
int print_percent(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
UNUSED(types);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
return (write(1, "%%", 1));
}

/** PRINT INT **/
/**
* print_int - it Print int
* @types: it  List a of arguments
* @buffer: a Buffer array to handle print
* @flags:  it Calculates active flags
* @width: a get width.
* @precision: the  Precision specification
* @size: a Size specifier
* Return: a Number of chars printed
*/
int print_int(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int u = BUFF_SIZE - 2;
int is_negative = 0;
long int n = va_arg(types, long int);
unsigned long int num;

n = convert_size_number(n, size);

if (n == 0)
buffer[u--] = '0';

buffer[BUFF_SIZE - 1] = '\0';
num = (unsigned long int)n;

if (n < 0)
{
num = (unsigned long int)((-1) * n);
is_negative = 1;
}

while (num > 0)
{
buffer[u--] = (num % 10) + '0';
num /= 10;
}

u++;

return (write_number(is_negative, u, buffer, flags, width, precision, size));
}

/* PRINT BINARY */
/**
* print_binary - it  Prints an unsigned number
* @types: it List a of arguments
* @buffer: a Buffer array to handle print
* @flags:  it Calculates active flags
* @width: a get width.
* @precision: the Precision specification
* @size: the Size specifier
* Return: the Numbers of char printed.
*/
int print_binary(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
unsigned int f, u, v, sum;
unsigned int a[32];
int count;

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

f = va_arg(types, unsigned int);
u = 2147483648; /* (2 ^ 31) */
a[0] = f / u;
for (v = 1; v < 32; v++)
{
u /= 2;
a[v] = (f / u) % 2;
}
for (v = 0, sum = 0, count = 0; v < 32; v++)
{
sum += a[v];
if (sum || v == 31)
{
char z = '0' + a[v];

write(1, &z, 1);
count++;
}
}
return (count);
}
