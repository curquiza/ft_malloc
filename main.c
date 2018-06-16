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

int		main(void)
{
	// char * a = malloc(-1);(void)a;
	// char * b = malloc(0);(void)b;

	// char * a = malloc(255);(void)a;
	// char * b = malloc(4100); (void)b;
	// char * c = malloc(12); (void)c;
	// char * d = malloc(0); (void)d;
	// char * e = malloc(0); (void)e;
	// char * f = malloc(20); (void)f;

	// test0();
	test1();

	// while(1);
	return (0);
}
