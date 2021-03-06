#include "dyn_alloc.h"
#include <stdio.h>

void	*malloc_basic_test(size_t size)
{
	size_t	i;
	char	*addr;

	addr = malloc(size);
	i = 0;
	while (i < size)
	{
		addr[i] = 'c';
		i++;
	}
	return (addr);
}

void	test_only_malloc(void)
{
	ft_putendl("--- ONLY MALLOC -------------------");
	malloc_basic_test(300);
	malloc_basic_test(700);
	malloc_basic_test(256);
	malloc_basic_test(4100);
	malloc_basic_test(824);
	malloc_basic_test(10000);
	malloc_basic_test(0);
	malloc_basic_test(1220);
	malloc_basic_test(8220);
	ft_putstr("\n");
	show_alloc_mem();
	ft_putendl("-----------------------------------");
}

void	test_malloc_free(void)
{
	ft_putendl("--- MALLOC FREE -------------------");
	char	*a;
	char	*b;
	char	*c;

	malloc_basic_test(1);
	a = malloc_basic_test(1024);
	b = malloc_basic_test(0);
	malloc_basic_test(1220);
	malloc_basic_test(12);
	malloc_basic_test(8220);
	c = malloc_basic_test(9220);
	malloc_basic_test(5024);
	ft_putstr("\nBEFORE FREE :\n");
	show_alloc_mem();
	ft_putstr("\n");
	free(a);
	free(c);
	free(b);
	ft_putstr("\nAFTER FREE :\n");
	show_alloc_mem();
	ft_putendl("-----------------------------------");
}

void	test_malloc_free2(void)
{
	ft_putendl("--- MALLOC FREE -------------------");
	char	*a;

	a = malloc_basic_test(1024);
	ft_putstr("\nBEFORE FREE :\n");
	show_alloc_mem();
	ft_putstr("\n");
	free(a);
	ft_putstr("\nAFTER FREE :\n");
	show_alloc_mem();
	ft_putendl("-----------------------------------");
}

void	test_realloc1(void)
{
	char *a;
	char *b;
	char *c;

	a = malloc_basic_test(10);
	printf("addr of a = %p\n", a);
	printf("a = %s\n", a);

	b = realloc(a, 16);
	printf("addr of b = %p\n", b);
	printf("b = %s\n", b);

	c = realloc(b, 32);
	printf("addr of c = %p\n", c);
	printf("c = %s\n", c);

	show_alloc_mem();
}

void	test_realloc2(void)
{
	char *a;
	char *b;
	char *c;

	a = malloc_basic_test(15);
	printf("addr of a = %p\n", a);
	a[15] = '\0';
	printf("a = %s\n", a);

	malloc_basic_test(15);

	b = realloc(a, 8007);
	printf("addr of b = %p\n", b);
	printf("b = %s\n", b);

	c = realloc(b, 7);
	printf("addr of d = %p\n", c);
	printf("c = %s\n", c);

	show_alloc_mem();
}

void	test_realloc3(void)
{
	char *a;
	char *b;

	a = malloc_basic_test(15);
	printf("addr of a = %p\n", a);

	b = realloc(a, 600);
	printf("addr of b = %p\n", b);

	show_alloc_mem();
}

void	test_realloc4(void)
{
	char *a;
	char *b;
	char *c;

	a = malloc_basic_test(89003);
	printf("addr of a = %p\n", a);

	b = realloc(a, 1093838);
	printf("addr of b = %p\n", b);

	c = realloc(NULL, 12);
	printf("addr of c = %p\n", c);
	show_alloc_mem();
}

void	test_defragm1(void)
{
	char	*a;
	char	*b;

	a = malloc_basic_test(89);
	b = malloc_basic_test(12);
	free(a);
	free(b);
	ft_putstr("\n");
	show_alloc_mem();
	ft_putstr("\n");
}

void	test_defragm2(void)
{
	char	*a;
	char	*b;
	char	*c;

	a = malloc_basic_test(654);
	b = malloc_basic_test(687);
	c = malloc_basic_test(965);
	free(c);
	free(a);
	free(b);
	ft_putstr("\n");
	show_alloc_mem();
	ft_putstr("\n");
}

void	test_defragm3(void)
{
	char	*a;
	char	*b;
	char	*c;

	a = malloc_basic_test(54155);
	b = malloc_basic_test(154142);
	c = malloc_basic_test(541551);
	free(b);
	free(c);
	free(a);
	ft_putstr("\n");
	show_alloc_mem();
	ft_putstr("\n");
}

void	test_defragm4(void)
{
	char	*a;
	char	*b;
	char	*c;

	a = malloc_basic_test(0);
	b = malloc_basic_test(0);
	c = malloc_basic_test(0);
	free(b);
	free(c);
	ft_putstr("\n");
	show_alloc_mem();
	ft_putstr("\n");
}

void	test_hex_dump1(void)
{
	char	*a;

	a = malloc(23);
	a[0] = 12;
	a[22] = 56;
	a[12] = 'c';
	hex_dump(a, 23);
}

void	test_hex_dump2(void)
{
	char	*a;

	a = malloc(32);
	a[0] = 12;
	a[22] = 56;
	a[6] = 'a';
	a[7] = '*';
	hex_dump(a, 32);
}

void	test_hex_dump3(void)
{
	int		*a;
	int		b;

	b = 12;
	a = &b;
	hex_dump(a, 8);
}

static size_t		ft_strlen(const char *s)
{
	int		cpt;

	cpt = -1;
	while (s[++cpt])
		;
	return (cpt);
}

static char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(*str) * (size + 1))))
		exit(1);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

static char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;
	int		len;

	len = ft_strlen(src);
	str = ft_strnew(len);
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	test_alloc_mem_hex(void)
{
	char	*a;

	ft_strdup("ciao les nazes !\n");
	a = ft_strdup("je vais free cette partie !\n");
	ft_strdup("je ne sais pas quoi ecrire !\n");
	free(a);
	ft_putstr("\n");
	show_alloc_mem_hex();
}

void	fuck_tests(void)
{
	char	*a;
	char	*b;
	char	*fuck;

	fuck = malloc(-1);
	a = malloc(0);
	fuck = realloc(a, -123);
	b = realloc(a, 0);
	fuck = calloc(-2, -2);
	fuck = calloc(0, 200);
	ft_putstr("\n");
	show_alloc_mem();
}

int		main(void)
{
	test_only_malloc();
	// ft_putstr("\n");
	// test_malloc_free();
	// test_malloc_free2();
	// ft_putstr("\n");
	//
	// test_realloc1();
	// test_realloc2();
	// test_realloc3();
	// test_realloc4();

	// test_defragm1();
	// test_defragm2();
	// test_defragm3();
	// test_defragm4();

	// test_hex_dump1();
	// ft_putstr("\n");
	// test_hex_dump2();
	// ft_putstr("\n");
	// test_hex_dump3();

	// test_alloc_mem_hex();

	// show_alloc_mem_hex();

	// fuck_tests();
	return (0);
}
