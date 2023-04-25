#include "main.h"
#include <limits.h>
#include <stdio.h>

/**
 * _printf - main
 * @format: Argument
 *
 * Return: Length of formatted output
 */
int _printf(const char *format, ...)
{
	int (*pfunc)(va_list, flags_t *);
	const char *p;
	va_list arguments;

	register int count = 0;

	flags_t flags = {0, 0, 0};

	va_start(arguments, format);

	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	for (p = format; *p; p++)
	{
		if (*p == '%')
		{
			p++;
			if (*p == '%')
			{
				count += _putchar('%');
				continue;
			}
			while (get_flag(*p, &flags))
				p++;
			pfunc = get_print(*p);
			count += (pfunc)
				? pfunc(arguments, &flags)
				: _printf("%%%c", *p);
		}
		else
			count += _putchar(*p);
	}
	_putchar(-1);
	va_end(arguments);
	return (count);
}
