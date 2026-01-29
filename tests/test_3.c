// tests_strl_bzero.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "libft.h" // твои прототипы: ft_strlcpy, ft_strlcat, ft_bzero

// ---- System reference for Linux(glibc) vs BSD/macOS ----
#if defined(__linux__)
#  include <bsd/string.h>   // strlcpy, strlcat, bzero from libbsd
#else
#  include <string.h>       // BSD/macOS: strlcpy/strlcat usually here
#endif

// ---- tiny test framework ----
#define TEST_START(name) do { printf("== %s ==\n", (name)); } while(0)

#define CHECK(cond) do { \
    if (!(cond)) { \
        printf("❌ FAIL at %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        exit(1); \
    } \
} while(0)

static void fill_pattern(unsigned char *p, size_t n, unsigned char v)
{
    for (size_t i = 0; i < n; i++) p[i] = v;
}

static int memeq(const void *a, const void *b, size_t n)
{
    return memcmp(a, b, n) == 0;
}

// ---------------------- ft_bzero tests ----------------------
static void test_bzero_basic(void)
{
    unsigned char a[16];
    unsigned char b[16];

    fill_pattern(a, sizeof(a), 0xAA);
    fill_pattern(b, sizeof(b), 0xAA);

    bzero(a, sizeof(a));
    ft_bzero(b, sizeof(b));

    CHECK(memeq(a, b, sizeof(a)));
    // sanity: must be all zeros
    for (size_t i = 0; i < sizeof(a); i++) CHECK(a[i] == 0);
}

static void test_bzero_zero_len(void)
{
    unsigned char a[8];
    unsigned char b[8];

    fill_pattern(a, sizeof(a), 0xAB);
    fill_pattern(b, sizeof(b), 0xAB);

    size_t n = 0;

    bzero(a, n);
    ft_bzero(b, n);


    CHECK(memeq(a, b, sizeof(a))); // nothing should change
}

static void test_bzero_partial(void)
{
    unsigned char a[10];
    unsigned char b[10];

    fill_pattern(a, sizeof(a), 0xCC);
    fill_pattern(b, sizeof(b), 0xCC);

    bzero(a + 3, 4);      // zero only bytes [3..6]
    ft_bzero(b + 3, 4);

    CHECK(memeq(a, b, sizeof(a)));
}

// ---------------------- ft_strlcpy tests ----------------------
static void run_strlcpy_case(const char *src, size_t dstsize)
{
    unsigned char ref[64];
    unsigned char got[64];

    // Fill whole buffers with pattern to detect over/under writes
    fill_pattern(ref, sizeof(ref), 0xEE);
    fill_pattern(got, sizeof(got), 0xEE);

    // Use only first N bytes as destination region
    // Compare return values and full 64 bytes to catch writing outside dstsize
    size_t r1 = strlcpy((char*)ref, src, dstsize);
    size_t r2 = ft_strlcpy((char*)got, src, dstsize);

    CHECK(r1 == r2);
    CHECK(memeq(ref, got, sizeof(ref)));
}

static void test_strlcpy_edges(void)
{
    run_strlcpy_case("", 0);
    run_strlcpy_case("", 1);
    run_strlcpy_case("A", 0);
    run_strlcpy_case("A", 1);
    run_strlcpy_case("A", 2);

    run_strlcpy_case("hello", 0);
    run_strlcpy_case("hello", 1);  // only '\0'
    run_strlcpy_case("hello", 2);  // "h\0"
    run_strlcpy_case("hello", 6);  // fits exactly with '\0'
    run_strlcpy_case("hello", 10); // bigger
}

static void test_strlcpy_long_src(void)
{
    char src[128];
    for (int i = 0; i < 127; i++) src[i] = (char)('a' + (i % 26));
    src[127] = '\0';

    run_strlcpy_case(src, 0);
    run_strlcpy_case(src, 1);
    run_strlcpy_case(src, 10);
    run_strlcpy_case(src, 64);
}

// ---------------------- ft_strlcat tests ----------------------
static void run_strlcat_case(const char *initial_dst, size_t dstsize, const char *src)
{
    unsigned char ref[64];
    unsigned char got[64];

    fill_pattern(ref, sizeof(ref), 0xDD);
    fill_pattern(got, sizeof(got), 0xDD);

    // Put initial_dst into the buffer in a controlled way.
    // We must not overflow while setting up; so we copy safely into full buffer.
    // Then we let strlcat operate with "dstsize".
    strlcpy((char*)ref, initial_dst, sizeof(ref));
    strlcpy((char*)got, initial_dst, sizeof(got));

    size_t r1 = strlcat((char*)ref, src, dstsize);
    size_t r2 = ft_strlcat((char*)got, src, dstsize);

    CHECK(r1 == r2);
    CHECK(memeq(ref, got, sizeof(ref)));
}

static void test_strlcat_edges(void)
{
    // dstsize = 0: should not touch dst, return dstsize + strlen(src)?? (BSD behavior)
    run_strlcat_case("", 0, "abc");
    run_strlcat_case("hi", 0, "abc");

    // dstsize small
    run_strlcat_case("", 1, "abc");       // only '\0'
    run_strlcat_case("h", 2, "abc");      // "h\0" (maybe no room)
    run_strlcat_case("hi", 3, "abc");     // "hi\0" no room to add
    run_strlcat_case("hi", 4, "abc");     // can add 1 char

    // fits
    run_strlcat_case("hi", 10, "abc");
    run_strlcat_case("", 10, "abc");
    run_strlcat_case("hello", 6, "X");    // exact size: no room to append
}

static void test_strlcat_long_src(void)
{
    char src[128];
    for (int i = 0; i < 127; i++) src[i] = (char)('0' + (i % 10));
    src[127] = '\0';

    run_strlcat_case("start", 0, src);
    run_strlcat_case("start", 5, src);
    run_strlcat_case("start", 10, src);
    run_strlcat_case("start", 64, src);
}

// ---------------------- main ----------------------
int main(void)
{
    TEST_START("ft_bzero");
    test_bzero_basic();
    test_bzero_zero_len();
    test_bzero_partial();

    TEST_START("ft_strlcpy");
    test_strlcpy_edges();
    test_strlcpy_long_src();

    TEST_START("ft_strlcat");
    test_strlcat_edges();
    test_strlcat_long_src();

    printf("✅ ALL TESTS PASSED\n");
    return 0;
}

