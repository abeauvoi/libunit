#include <stdlib.h>
#include <unistd.h>
#include "libunit.h"

#define BUF_SIZE (3 * sizeof(int) + 2)

size_t 	ft_strlen(const char *str)
{
	const char 	*str0;

	str0 = str;
	while (*str != '\0')
		++str;
	return (str - str0);
}

void 	ft_putstr(const char *str)
{
	if (write(1, str, ft_strlen(str)) == -1)
		exit(EXIT_FAILURE);
}

void 	ft_putnbr(int nb)
{
	char 			buf[BUF_SIZE];
	char 			*ptr;
	unsigned int 	unb;
	unsigned int 	is_negative;

	ptr = buf + BUF_SIZE - 1;
	*ptr = '\0';
	is_negative = nb < 0;
	unb = (is_negative ? -nb : nb);
	if (unb == 0)
		*--ptr = '0';
	else
	{
		while (unb > 0)
		{
			*--ptr = (unb % 10) + '0';
			unb /= 10;
		}
		if (is_negative)
			*ptr = '-';
	}
	ft_putstr(ptr);
}
