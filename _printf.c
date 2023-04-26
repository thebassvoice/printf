#include "main.h"

void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - Printf function
 * @format: pointer
 * Return: chars.
 */
int _printf(const char *format, ...)
{
	int e, print = 0, print_chars = 0;
	int f, width, pre, size, buff_ind = 0;
	va_list l;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(l, format);

	for (e = 0; format && format[e] != '\0'; e++)
	{
		if (format[e] != '%')
		{
			buffer[buff_ind++] = format[e];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			print_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			f = get_flags(format, &e);
			width = get_width(format, &e, l);
			pre = get_pre(format, &e, l);
			size = get_size(format, &e);
			++e;
			print = handle_print(format, &e, l, buffer,
				f, width, pre, size);
			if (print == -1)
				return (-1);
			print_chars += print;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(l);
	return (print_chars);
}

/**
 * print_buffer - Function
 * @buffer: argument
 * @buff_ind: pointer
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
