#include <stdarg.h>
#include "main.h"
#include <stddef.h>
/**
 * get_op - main funtion
 * @c: argument
 * Return: Null
 */

int (*get_op(const char c))(va_list)
{
	int e = 0;

	flags_p fp[] = {
		{"c", print_char},
		{"s", print_str},
		{"i", print_nbr},
		{"d", print_nbr},
		{"b", print_binary},
		{"o", print_octal},
		{"x", print_hexa_lower},
		{"X", print_hexa_upper},
		{"u", print_unsigned},
		{"S", print_str_unprintable},
		{"r", print_str_reverse},
		{"p", print_ptr},
		{"R", print_rot13},
		{"%", print_percent}
	};
	while (e < 14)
	{
		if (c == fp[e].c[0])
		{
			return (fp[e].f);
		}
		e++;
	}
	return (NULL);
}

/**
 * _printf - printf function
 * @format: argument
 * Return: NULL
 */

int _printf(const char *format, ...)
{
	va_list ap;
	int total = 0, e = 0;
	int (*func)();

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	va_start(ap, format);

	while (format[e])
	{
		if (format[e] == '%')
		{
			if (format[e + 1] != '\0')
				func = get_op(format[e + 1]);
			if (func == NULL)
			{
				_putchar(format[e]);
				total++;
				e++;
			}
			else
			{
				total += func(ap);
				e += 2;
				continue;
			}
		}
		else
		{
			_putchar(format[e]);
			total++;
			e++;
		}
	}
	va_end(ap);
	return (total);
}
