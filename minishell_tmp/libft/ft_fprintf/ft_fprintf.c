/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:16:56 by yseto             #+#    #+#             */
/*   Updated: 2025/09/30 21:16:48 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static char	*int_to_str(int n)
{
	char	buf[12];
	int		i;
	int		neg;
	char	*res;

	i = 11;
	neg = 0;
	buf[i--] = '\0';
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	while (n)
	{
		buf[i--] = '0' + (n % 10);
		n /= 10;
	}
	if (neg)
		buf[i--] = '-';
	i++;
	res = ft_strdup(buf + i);
	return (res);
}

static int	putnbr_file(FILE *stream, int n)
{
	char	*str;
	int		len;
	int		i;

	str = int_to_str(n);
	if (!str)
		return (-1);
	len = 0;
	i = 0;
	while (str[i])
	{
		len += putchar_file(stream, str[i]);
		i++;
	}
	free(str);
	return (len);
}

static int	handle_format(FILE *stream, char spec, va_list args)
{
	if (spec == 's')
		return (putstr_file(stream, va_arg(args, char *)));
	else if (spec == 'd')
		return (putnbr_file(stream, va_arg(args, int)));
	else if (spec == 'c')
		return (putchar_file(stream, va_arg(args, int)));
	else
		return (putchar_file(stream, spec));
}

int	ft_fprintf(FILE *stream, const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			len += handle_format(stream, format[i], args);
		}
		else
			len += putchar_file(stream, format[i]);
		i++;
	}
	va_end(args);
	return (len);
}

// int	main(void)
// {
// 	FILE	*fp;
// 	int		len;

// 	// ファイルを開く（書き込み用）
// 	fp = fopen("test_output.txt", "w");
// 	if (!fp)
// 	{
// 		perror("fopen");
// 		return (1);
// 	}
// 	// 文字列、数値、文字を出力して文字数を確認
// 	len = ft_fprintf(fp, "Hello %s!\nNumber: %d\nChar: %c\n", "world", 42, 'A');
// 	printf("ft_fprintf wrote %d characters\n", len);
// 	fclose(fp);
// 	// 標準出力にもテスト
// 	len = ft_fprintf(stdout, "Printing to stdout: %s %d %c\n", "Test", 123,
// 			'Z');
// 	printf("ft_fprintf wrote %d characters to stdout\n", len);
// 	return (0);
// }
