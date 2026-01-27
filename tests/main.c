#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../libft.h"

static int g_total = 0;
static int g_failed = 0;

#define TEST_START(name) do { \
    printf("\n== %s ==\n", (name)); \
} while(0)

#define CHECK(cond, msg) do { \
    g_total++; \
    if (!(cond)) { \
        g_failed++; \
        printf("[FAIL] %s (line %d): %s\n", __FILE__, __LINE__, (msg)); \
    } else { \
        printf("[ OK ] %s\n", (msg)); \
    } \
} while(0)

#define BOOL_EQ(a, b) (((a) != 0) == ((b) != 0))

static void test_is_functions(void)
{
    TEST_START("isalpha/isdigit/isalnum/isascii/isprint");

    int values[] = { 'A', 'z', '0', '9', '@', '{', ' ', '\n', 0, 127, 128, -1, 255 };
    size_t n = sizeof(values)/sizeof(values[0]);

    for (size_t i = 0; i < n; i++) {
        int c = values[i];

        CHECK(BOOL_EQ(ft_isalpha(c), isalpha((unsigned char)c)), "isalpha compare with libc");
        CHECK(BOOL_EQ(ft_isdigit(c), isdigit((unsigned char)c)), "isdigit compare with libc");
        CHECK(BOOL_EQ(ft_isalnum(c), isalnum((unsigned char)c)), "isalnum compare with libc");
        CHECK(BOOL_EQ(ft_isascii(c), isascii(c)),               "isascii compare with libc");
        CHECK(BOOL_EQ(ft_isprint(c), isprint((unsigned char)c)), "isprint compare with libc");
    }
}

static void test_toupper_tolower(void)
{
    TEST_START("toupper/tolower");

    int values[] = { 'a', 'z', 'A', 'Z', '0', '@', 0, 127, 128, -1 };
    size_t n = sizeof(values)/sizeof(values[0]);

    for (size_t i = 0; i < n; i++) {
        int c = values[i];

        int libc_up = (c == EOF) ? toupper(EOF) : toupper((unsigned char)c);
        int libc_lo = (c == EOF) ? tolower(EOF) : tolower((unsigned char)c);

        CHECK(ft_toupper(c) == libc_up, "toupper compare with libc");
        CHECK(ft_tolower(c) == libc_lo, "tolower compare with libc");
    }
}


static void test_strlen(void)
{
    TEST_START("strlen");

    const char *cases[] = { "", "a", "hello", "0123456789", "test\0hidden" };
    size_t n = sizeof(cases)/sizeof(cases[0]);

    for (size_t i = 0; i < n; i++) {
        CHECK(ft_strlen(cases[i]) == strlen(cases[i]), "strlen compare with libc");
    }
}

static void test_memset_bzero(void)
{
    TEST_START("memset/bzero");

    unsigned char a1[16];
    unsigned char a2[16];

    memset(a1, 0xAA, sizeof(a1));
    memset(a2, 0xAA, sizeof(a2));

    ft_memset(a1, 0x5B, 10);
    memset(a2, 0x5B, 10);
    CHECK(memcmp(a1, a2, sizeof(a1)) == 0, "memset content");

    memset(a1, 0xAA, sizeof(a1));
    memset(a2, 0xAA, sizeof(a2));
    ft_bzero(a1, 7);
    bzero(a2, 7);
    CHECK(memcmp(a1, a2, sizeof(a1)) == 0, "bzero content");
}

static void test_memcpy_memmove(void)
{
    TEST_START("memcpy/memmove");

    unsigned char s1[32];
    unsigned char s2[32];
    for (int i = 0; i < 32; i++) { s1[i] = (unsigned char)i; s2[i] = (unsigned char)i; }

    unsigned char d1[32];
    unsigned char d2[32];
    memset(d1, 0, sizeof(d1));
    memset(d2, 0, sizeof(d2));

    ft_memcpy(d1, s1, 20);
    memcpy(d2, s2, 20);
    CHECK(memcmp(d1, d2, 32) == 0, "memcpy basic");

    // memmove overlap tests
    unsigned char o1[20] = "abcdefghijklmnopqrs";
    unsigned char o2[20] = "abcdefghijklmnopqrs";

    ft_memmove(o1 + 2, o1, 10);
    memmove(o2 + 2, o2, 10);
    CHECK(memcmp(o1, o2, sizeof(o1)) == 0, "memmove overlap right");

    unsigned char o3[20] = "abcdefghijklmnopqrs";
    unsigned char o4[20] = "abcdefghijklmnopqrs";

    ft_memmove(o3, o3 + 2, 10);
    memmove(o4, o4 + 2, 10);
    CHECK(memcmp(o3, o4, sizeof(o3)) == 0, "memmove overlap left");
}

static void test_strchr_strrchr_strncmp(void)
{
    TEST_START("strchr/strrchr/strncmp");

    const char *s = "hello world";

    CHECK(ft_strchr(s, 'o') == strchr(s, 'o'), "strchr pointer compare");
    CHECK(ft_strchr(s, '\0') == strchr(s, '\0'), "strchr for NUL");
    CHECK(ft_strrchr(s, 'l') == strrchr(s, 'l'), "strrchr pointer compare");
    CHECK(ft_strrchr(s, '\0') == strrchr(s, '\0'), "strrchr for NUL");

    CHECK(ft_strncmp("abc", "abc", 3) == strncmp("abc", "abc", 3), "strncmp equal");
    CHECK(ft_strncmp("abc", "abd", 3) == strncmp("abc", "abd", 3), "strncmp diff");
    CHECK(ft_strncmp("abc", "abc", 0) == strncmp("abc", "abc", 0), "strncmp n=0");
}

static void test_memchr_memcmp(void)
{
    TEST_START("memchr/memcmp");

    unsigned char buf[] = { 1, 2, 3, 4, 5, 0, 7 };

    CHECK(ft_memchr(buf, 4, 7) == memchr(buf, 4, 7), "memchr found");
    CHECK(ft_memchr(buf, 9, 7) == memchr(buf, 9, 7), "memchr not found");
    CHECK(ft_memchr(buf, 1, 0) == memchr(buf, 1, 0), "memchr n=0");

    CHECK(ft_memcmp("abc", "abc", 3) == memcmp("abc", "abc", 3), "memcmp equal");
    CHECK(ft_memcmp("abc", "abd", 3) == memcmp("abc", "abd", 3), "memcmp diff");
}

static void test_atoi(void)
{
    TEST_START("atoi");

    const char *cases[] = {
        "42",
        "   -42",
        "   +42",
        "4193 with words",
        "words 123",
        "-0012a42",
        "   \t\n  214"
    };
    size_t n = sizeof(cases)/sizeof(cases[0]);

    for (size_t i = 0; i < n; i++) {
        CHECK(ft_atoi(cases[i]) == atoi(cases[i]), "atoi compare with libc");
    }
}

static void test_calloc_strdup(void)
{
    TEST_START("calloc/strdup");

    // calloc: basic zeroing
    size_t n = 10;
    int *p = (int *)ft_calloc(n, sizeof(int));
    CHECK(p != NULL, "calloc returns non-NULL for normal case");
    if (p) {
        int ok = 1;
        for (size_t i = 0; i < n; i++) {
            if (p[i] != 0) { ok = 0; break; }
        }
        CHECK(ok, "calloc zeroed memory");
        free(p);
    }

    // calloc: project rule for 0
    void *z1 = ft_calloc(0, 10);
    void *z2 = ft_calloc(10, 0);
    CHECK(z1 != NULL, "calloc(0,10) returns unique pointer (project rule)");
    CHECK(z2 != NULL, "calloc(10,0) returns unique pointer (project rule)");
    free(z1);
    free(z2);

    // strdup
    const char *s = "hello";
    char *d = ft_strdup(s);
    CHECK(d != NULL, "strdup returns non-NULL");
    if (d) {
        CHECK(strcmp(d, s) == 0, "strdup content equals");
        CHECK(d != s, "strdup pointer different");
        free(d);
    }
}

int main(void)
{
    test_is_functions();
    test_toupper_tolower();
    test_strlen();
    test_memset_bzero();
    test_memcpy_memmove();
    test_strchr_strrchr_strncmp();
    test_memchr_memcmp();
    test_atoi();
    test_calloc_strdup();

    printf("\nTOTAL: %d, FAILED: %d\n", g_total, g_failed);
    return (g_failed != 0);
}

