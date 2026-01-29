#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int g_pass = 0;
static int g_fail = 0;

#define TEST(name) do { \
    printf("\n== %s ==\n", (name)); \
} while (0)

#define CHECK(cond) do { \
    if (cond) { g_pass++; printf("✅ %s\n", #cond); } \
    else      { g_fail++; printf("❌ %s (line %d)\n", #cond, __LINE__); } \
} while (0)

static void del_str(void *p) { free(p); }

static void del_int(void *p) { free(p); }

static void iter_to_upper_first_char(void *p)
{
    char *s = (char *)p;
    if (!s || !s[0]) return;
    if (s[0] >= 'a' && s[0] <= 'z') s[0] = (char)(s[0] - 'a' + 'A');
}

static void *map_strdup_add_suffix(void *p)
{
    const char *s = (const char *)p;
    if (!s) return NULL;
    size_t n = strlen(s);
    char *out = (char *)malloc(n + 3); /* "_x" + '\0' */
    if (!out) return NULL;
    memcpy(out, s, n);
    out[n] = '_';
    out[n + 1] = 'x';
    out[n + 2] = '\0';
    return out;
}

/* map function that allocates memory (int) */
static void *map_int_times2(void *p)
{
    int *x = (int *)p;
    int *out = (int *)malloc(sizeof(int));
    if (!out) return NULL;
    *out = x ? (*x * 2) : 0;
    return out;
}

/* Map function that returns malloc'ed content, but we can force node alloc fail only
 * with custom malloc, so here we just test normal flow + NULL f handling. */
static void *map_returns_null(void *p)
{
    (void)p;
    return NULL;
}

static char *xstrdup(const char *s)
{
    size_t n = strlen(s);
    char *out = (char *)malloc(n + 1);
    if (!out) return NULL;
    memcpy(out, s, n + 1);
    return out;
}

static int *mk_int(int v)
{
    int *p = (int *)malloc(sizeof(int));
    if (!p) return NULL;
    *p = v;
    return p;
}

/* ---------- tests ---------- */
static void test_lstnew(void)
{
    TEST("ft_lstnew");

    t_list *n1 = ft_lstnew(NULL);
    CHECK(n1 != NULL);
    CHECK(n1->content == NULL);
    CHECK(n1->next == NULL);
    free(n1);

    char *s = xstrdup("hello");
    t_list *n2 = ft_lstnew(s);
    CHECK(n2 != NULL);
    CHECK(n2->content == s);
    CHECK(n2->next == NULL);
    /* content is owned by us; for this test free manually */
    free(s);
    free(n2);
}

static void test_lstadd_front_size_last(void)
{
    TEST("ft_lstadd_front + ft_lstsize + ft_lstlast");

    t_list *lst = NULL;

    CHECK(ft_lstsize(lst) == 0);
    CHECK(ft_lstlast(lst) == NULL);

    t_list *a = ft_lstnew(xstrdup("a"));
    ft_lstadd_front(&lst, a);
    CHECK(lst == a);
    CHECK(ft_lstsize(lst) == 1);
    CHECK(ft_lstlast(lst) == a);

    t_list *b = ft_lstnew(xstrdup("b"));
    ft_lstadd_front(&lst, b);
    CHECK(lst == b);
    CHECK(ft_lstsize(lst) == 2);
    CHECK(ft_lstlast(lst) == a);

    ft_lstclear(&lst, del_str);
    CHECK(lst == NULL);
}

static void test_lstadd_back(void)
{
    TEST("ft_lstadd_back");

    t_list *lst = NULL;

    t_list *a = ft_lstnew(xstrdup("a"));
    ft_lstadd_back(&lst, a);
    CHECK(lst == a);
    CHECK(ft_lstlast(lst) == a);
    CHECK(ft_lstsize(lst) == 1);

    t_list *b = ft_lstnew(xstrdup("b"));
    ft_lstadd_back(&lst, b);
    CHECK(ft_lstlast(lst) == b);
    CHECK(ft_lstsize(lst) == 2);
    CHECK(a->next == b);
    CHECK(b->next == NULL);

    ft_lstclear(&lst, del_str);
    CHECK(lst == NULL);
}

static void test_lstdelone(void)
{
    TEST("ft_lstdelone");

    char *s = xstrdup("bye");
    t_list *n = ft_lstnew(s);

    /* should free content via del and node itself */
    ft_lstdelone(n, del_str);

    /* Can't safely touch n here: it was freed. Just ensure no crash. */
    CHECK(1);
}

static void test_lstclear(void)
{
    TEST("ft_lstclear");

    t_list *lst = NULL;
    ft_lstclear(&lst, del_str);
    CHECK(lst == NULL);

    ft_lstadd_back(&lst, ft_lstnew(xstrdup("a")));
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("b")));
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("c")));
    CHECK(ft_lstsize(lst) == 3);

    ft_lstclear(&lst, del_str);
    CHECK(lst == NULL);

    /* clear twice shouldn't crash */
    ft_lstclear(&lst, del_str);
    CHECK(lst == NULL);
}

static void test_lstiter(void)
{
    TEST("ft_lstiter");

    t_list *lst = NULL;
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("abc")));
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("def")));
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("ghi")));

    ft_lstiter(lst, iter_to_upper_first_char);

    CHECK(strcmp((char *)lst->content, "Abc") == 0);
    CHECK(strcmp((char *)lst->next->content, "Def") == 0);
    CHECK(strcmp((char *)lst->next->next->content, "Ghi") == 0);

    ft_lstclear(&lst, del_str);
    CHECK(lst == NULL);
}

static void test_lstmap_strings(void)
{
    TEST("ft_lstmap (strings)");

    t_list *lst = NULL;
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("a")));
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("bb")));
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("ccc")));

    t_list *mapped = ft_lstmap(lst, map_strdup_add_suffix, del_str);
    CHECK(mapped != NULL);
    CHECK(ft_lstsize(mapped) == 3);

    CHECK(strcmp((char *)mapped->content, "a_x") == 0);
    CHECK(strcmp((char *)mapped->next->content, "bb_x") == 0);
    CHECK(strcmp((char *)mapped->next->next->content, "ccc_x") == 0);

    /* original must remain unchanged */
    CHECK(strcmp((char *)lst->content, "a") == 0);

    ft_lstclear(&lst, del_str);
    ft_lstclear(&mapped, del_str);
    CHECK(lst == NULL);
    CHECK(mapped == NULL);
}

static void test_lstmap_ints(void)
{
    TEST("ft_lstmap (ints)");

    t_list *lst = NULL;
    ft_lstadd_back(&lst, ft_lstnew(mk_int(2)));
    ft_lstadd_back(&lst, ft_lstnew(mk_int(5)));
    ft_lstadd_back(&lst, ft_lstnew(mk_int(-3)));

    t_list *mapped = ft_lstmap(lst, map_int_times2, del_int);
    CHECK(mapped != NULL);
    CHECK(ft_lstsize(mapped) == 3);

    CHECK(*(int *)mapped->content == 4);
    CHECK(*(int *)mapped->next->content == 10);
    CHECK(*(int *)mapped->next->next->content == -6);

    /* original unchanged */
    CHECK(*(int *)lst->content == 2);

    ft_lstclear(&lst, del_int);
    ft_lstclear(&mapped, del_int);
}

static void test_lstmap_edge_cases(void)
{
    TEST("ft_lstmap edge cases");

    t_list *lst = NULL;
    ft_lstadd_back(&lst, ft_lstnew(xstrdup("a")));

    CHECK(ft_lstmap(lst, NULL, del_str) == NULL);

    /* f returns NULL content: list nodes should still be created (content NULL) */
    t_list *mapped = ft_lstmap(lst, map_returns_null, del_str);
    CHECK(mapped != NULL);
    CHECK(ft_lstsize(mapped) == 1);
    CHECK(mapped->content == NULL);

    ft_lstclear(&lst, del_str);
    ft_lstclear(&mapped, del_str);
}

int main(void)
{
    test_lstnew();
    test_lstadd_front_size_last();
    test_lstadd_back();
    test_lstdelone();
    test_lstclear();
    test_lstiter();
    test_lstmap_strings();
    test_lstmap_ints();
    test_lstmap_edge_cases();

    printf("\n========================\n");
    printf("PASS: %d\n", g_pass);
    printf("FAIL: %d\n", g_fail);
    printf("========================\n");

    return (g_fail == 0 ? 0 : 1);
}

