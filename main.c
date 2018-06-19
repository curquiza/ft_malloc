#include "dyn_alloc.h"

void	test0(void)
{
	int i;
	char *addr;

	(void)addr;
	i = 0;
	while (i < 1024)
	{
		i++;
	}
}

void	test1(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
}

void	malloc_test(size_t size)
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
}

int		main(void)
{
	// char * a = malloc(-1);(void)a;

	// malloc_test(255);
	// malloc_test(300);
	// malloc_test(700);
	// malloc_test(256);
	// malloc_test(4100);
	// malloc_test(824);
	// malloc_test(1220);
	// malloc_test(8220);
	// malloc_test(1000);
	// malloc_test(1);
	// malloc_test(12);
	// malloc_test(0);
	// malloc_test(0);
	// malloc_test(20);
	// malloc_test(1);
	// malloc_test(0);
	// malloc_test(16);
	// malloc_test(17);
	// malloc_test(15);

	// test0();
	// test1();

	char * add = malloc(1); (void)add;
	char * add2 = malloc(123423); (void)add2;
	char * add3 = malloc(123); (void)add3;
	show_alloc_mem();

	// while(1);
	return (0);
}
