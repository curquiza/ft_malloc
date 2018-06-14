#include "dyn_alloc.h"

int		main(void)
{
	char * a = malloc(-1);(void)a;
	char * b = malloc(0);(void)b;

	// char * a = malloc(255);(void)a;
	// char * b = malloc(4100); (void)b;
	// char * c = malloc(12); (void)c;
	// char * d = malloc(0); (void)d;
	// char * e = malloc(0); (void)e;
	// char * f = malloc(20); (void)f;

	// while(1);
	return (0);
}
