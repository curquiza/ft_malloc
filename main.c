#include "dyn_alloc.h"

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

int		main(void)
{
	test_only_malloc();
	ft_putstr("\n");
	test_malloc_free();
	return (0);
}
