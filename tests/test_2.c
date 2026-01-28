/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: you <you@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28                                    #+#    #+#       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "libft.h"

/* ------------------------- tiny test macros ------------------------- */

static int g_fail = 0;
static int g_pass = 0;

#define CHECK(cond) do { \
	if (cond) { g_pass++; } \
	else { g_fail++; printf("❌ FAIL at %s:%d: %s\n", __FILE__, __LINE__, #cond); } \
} while (0)

static void check_streq(const char *got, const char *exp)
{
    if (!got || !exp)
    {
        if (got != exp)
            printf("GOT=%p EXP=%p\n", (void *)got, (void *)exp);
        CHECK(got == exp);
        return;
    }
    if (strcmp(got, exp) != 0)
        printf("GOT:\"%s\"\nEXP:\"%s\"\n", got, exp);
    CHECK(strcmp(got, exp) == 0);
}

static void check_ptr_null(const void *p)
{
	CHECK(p == NULL);
}

static void free_split(char **arr)
{
	size_t i = 0;
	if (!arr) return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void check_split_eq(char **got, const char **exp) /* exp must end with NULL */
{
	size_t i = 0;

	if (!got || !exp)
	{
		CHECK(got == (char **)exp);
		return;
	}
	while (exp[i] && got[i])
	{
		CHECK(strcmp(got[i], exp[i]) == 0);
		i++;
	}
	CHECK(got[i] == NULL && exp[i] == NULL);
}

/* ------------------------- capture output helpers ------------------------- */

static char *read_all_fd(int fd)
{
	char	buf[256];
	ssize_t	n;
	size_t	cap = 256;
	size_t	len = 0;
	char	*out = (char *)malloc(cap);

	if (!out) return NULL;
	while ((n = read(fd, buf, sizeof(buf))) > 0)
	{
		if (len + (size_t)n + 1 > cap)
		{
			size_t new_cap = cap * 2;
			while (new_cap < len + (size_t)n + 1)
				new_cap *= 2;
			char *tmp = (char *)realloc(out, new_cap);
			if (!tmp)
			{
				free(out);
				return NULL;
			}
			out = tmp;
			cap = new_cap;
		}
		memcpy(out + len, buf, (size_t)n);
		len += (size_t)n;
	}
	out[len] = '\0';
	return out;
}

static char *capture_putchar(char c)
{
	int p[2];
	char *out;

	if (pipe(p) != 0) return NULL;
	ft_putchar_fd(c, p[1]);
	close(p[1]);
	out = read_all_fd(p[0]);
	close(p[0]);
	return out;
}

static char *capture_putstr(char *s)
{
	int p[2];
	char *out;

	if (pipe(p) != 0) return NULL;
	ft_putstr_fd(s, p[1]);
	close(p[1]);
	out = read_all_fd(p[0]);
	close(p[0]);
	return out;
}

static char *capture_putendl(char *s)
{
	int p[2];
	char *out;

	if (pipe(p) != 0) return NULL;
	ft_putendl_fd(s, p[1]);
	close(p[1]);
	out = read_all_fd(p[0]);
	close(p[0]);
	return out;
}

static char *capture_putnbr(int n)
{
	int p[2];
	char *out;

	if (pipe(p) != 0) return NULL;
	ft_putnbr_fd(n, p[1]);
	close(p[1]);
	out = read_all_fd(p[0]);
	close(p[0]);
	return out;
}

/* ------------------------- funcs for mapi/iteri ------------------------- */

static char f_mapi(unsigned int i, char c)
{
	/* shift letters by index (wrap only for lowercase a-z just for testing) */
	if (c >= 'a' && c <= 'z')
		return (char)('a' + (c - 'a' + (int)(i % 26)) % 26);
	return c;
}

static void f_iteri(unsigned int i, char *c)
{
	/* uppercase every even index */
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c = (char)(*c - 32);
}

/* ------------------------- tests ------------------------- */

static void test_substr(void)
{
	char *s;

	s = ft_substr("Hello world", 0, 5);
	check_streq(s, "Hello");
	free(s);

	s = ft_substr("Hello world", 6, 5);
	check_streq(s, "world");
	free(s);

	s = ft_substr("Hello", 10, 3);
	check_streq(s, "");
	free(s);

	s = ft_substr("", 0, 10);
	check_streq(s, "");
	free(s);

	s = ft_substr(NULL, 0, 3);
	check_ptr_null(s);
}

static void test_strjoin(void)
{
	char *s;

	s = ft_strjoin("abc", "def");
	check_streq(s, "abcdef");
	free(s);

	s = ft_strjoin("", "x");
	check_streq(s, "x");
	free(s);

	s = ft_strjoin("x", "");
	check_streq(s, "x");
	free(s);

	s = ft_strjoin(NULL, "x");
	check_ptr_null(s);

	s = ft_strjoin("x", NULL);
	check_ptr_null(s);
}

static void test_strtrim(void)
{
	char *s;

	s = ft_strtrim("   hello  ", " ");
	check_streq(s, "hello");
	free(s);

	s = ft_strtrim("xxxyhelloxxx", "x");
	check_streq(s, "yhello");
	free(s);

	s = ft_strtrim("xxxx", "x");
	check_streq(s, "");
	free(s);

	s = ft_strtrim("", "x");
	check_streq(s, "");
	free(s);

	s = ft_strtrim(NULL, "x");
	check_ptr_null(s);

	s = ft_strtrim("abc", NULL);
	check_ptr_null(s);
}

static void test_split(void)
{
	char **arr;

	{
		const char *exp[] = {"a", "b", "c", NULL};
		arr = ft_split("a b c", ' ');
		check_split_eq(arr, exp);
		free_split(arr);
	}
	{
		const char *exp[] = {"hello", "world", NULL};
		arr = ft_split("   hello   world  ", ' ');
		check_split_eq(arr, exp);
		free_split(arr);
	}
	{
		const char *exp[] = {"a", "b", "c", NULL};
		arr = ft_split("a,,b,,,c", ',');
		check_split_eq(arr, exp);
		free_split(arr);
	}
	{
		const char *exp[] = {NULL};
		arr = ft_split("", ' ');
		check_split_eq(arr, exp);
		free_split(arr);
	}
	{
		const char *exp[] = {NULL};
		arr = ft_split(",,,", ',');
		check_split_eq(arr, exp);
		free_split(arr);
	}

	arr = ft_split(NULL, ' ');
	check_ptr_null(arr);
}

static void test_itoa(void)
{
	char *s;
	char exp[64];

	s = ft_itoa(0);
	check_streq(s, "0");
	free(s);

	s = ft_itoa(42);
	check_streq(s, "42");
	free(s);

	s = ft_itoa(-42);
	check_streq(s, "-42");
	free(s);

	snprintf(exp, sizeof(exp), "%d", INT_MAX);
	s = ft_itoa(INT_MAX);
	check_streq(s, exp);
	free(s);

	snprintf(exp, sizeof(exp), "%d", INT_MIN);
	s = ft_itoa(INT_MIN);
	check_streq(s, exp);
	free(s);
}

static void test_strmapi(void)
{
	char *s;

	s = ft_strmapi("abcd", f_mapi);
	check_streq(s, "aceg"); /* a+(0)=a, b+(1)=c, c+(2)=e, d+(3)=g */
	free(s);

	s = ft_strmapi("", f_mapi);
	check_streq(s, "");
	free(s);

	s = ft_strmapi(NULL, f_mapi);
	check_ptr_null(s);

	s = ft_strmapi("abc", NULL);
	check_ptr_null(s);
}

static void test_striteri(void)
{
	char buf1[] = "hello";
	char buf2[] = "";
	char *pnull = NULL;

	ft_striteri(buf1, f_iteri);
	check_streq(buf1, "HELLO");

	ft_striteri(buf2, f_iteri);
	check_streq(buf2, "");

	/* should not crash / do nothing */
	ft_striteri(pnull, f_iteri);
	ft_striteri("nope", NULL);
	CHECK(1);
}

static void test_put_fd(void)
{
	char *out;
	char exp[64];

	out = capture_putchar('A');
	check_streq(out, "A");
	free(out);

	out = capture_putstr("Hello");
	check_streq(out, "Hello");
	free(out);

	out = capture_putstr(NULL);
	check_streq(out, ""); /* your ft_putstr_fd should do nothing on NULL */
	free(out);

	out = capture_putendl("Hi");
	check_streq(out, "Hi\n");
	free(out);

	out = capture_putendl("");
	check_streq(out, "\n");
	free(out);

	snprintf(exp, sizeof(exp), "%d", 12345);
	out = capture_putnbr(12345);
	check_streq(out, exp);
	free(out);

	snprintf(exp, sizeof(exp), "%d", -9876);
	out = capture_putnbr(-9876);
	check_streq(out, exp);
	free(out);

	snprintf(exp, sizeof(exp), "%d", INT_MIN);
	out = capture_putnbr(INT_MIN);
	check_streq(out, exp);
	free(out);

	snprintf(exp, sizeof(exp), "%d", INT_MAX);
	out = capture_putnbr(INT_MAX);
	check_streq(out, exp);
	free(out);
}

int main(void)
{
	test_substr();
	test_strjoin();
	test_strtrim();
	test_split();
	test_itoa();
	test_strmapi();
	test_striteri();
	test_put_fd();

	printf("\n✅ PASS: %d\n", g_pass);
	printf("❌ FAIL: %d\n", g_fail);
	return (g_fail != 0);
}

