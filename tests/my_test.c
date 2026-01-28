#include <ctype.h>
#include "libft.h"
#include <stdio.h>

static int	g_total = 0;
static int	g_failed = 0;

#define TEST_START(name) do { \
	printf("\n==%s==\n", (name)); \
} while(0)

#define CHECK(cond , msg) do { \
	g_total++; \
	if(!(cond)) { \
		g_failed++; \
		printf("[FAIL] %s (line %d): %s\n", __FILE__, __LINE__, (msg)); \
		} else { \
			printf("[OK] %s\n", (msg)); \
		}\
} while(0)

static void test_is_functions(void)
{
	TEST_START("isalpha/isdigit/isalnum/isascii/isprint");

	int values[] = { 'A', 'z', '0', '9', '@', '{', ' ', '\n', 0, 127, 128, -1, 255 };
	size_t n = sizeof(values) / sizeof(values[0]);

	for(size_t i = 0; i < n; i++)
	{
		int c = values[i];
		unsigned char uc = (unsigned char)c;

		CHECK(((ft_isalpha(c) != 0) == (isalpha(uc) != 0)), "isalpha compare with libc");
		CHECK(((ft_isdigit(c) != 0) == (isdigit(uc) != 0)), "isdigit compare with libc");
		CHECK(((ft_isalnum(c) != 0) == (isalnum(uc) != 0)), "isalnum compare with libc");
		CHECK(((ft_isascii(c) != 0) == (isascii(c) != 0)),   "isascii compare with libc");
		CHECK(((ft_isprint(c) != 0) == (isprint(uc) != 0)),   "isprint compare with libc");
	}
}

static void test_toupper_tolower(void)
{
	TEST_START("toupper / tolower");

	int values[] = {'a', 'z', 'A', 'Z', '0', '@', ' ', 0, 127, 128, -1 };
	size_t n = sizeof(values) / sizeof(values[0]);

	for(size_t i = 0; i < n; i++)
	{
		int c = values[i];

		int libc_up = (c == EOF) ? toupper(EOF) : toupper((unsigned char)c);
		int libc_lo = (c == EOF) ? tolower(EOF) : tolower((unsigned char)c);

		CHECK(ft_toupper(c) == libc_up, "toupper compare with libc");
		CHECK(ft_tolower(c) == libc_lo, "tolower compare with libc");
	}
}

int main()
{
	test_is_functions();
	test_toupper_tolower();

	printf("\nTotal: %d , Failed: %d\n", g_total, g_failed);
	return (g_failed != 0);
}
