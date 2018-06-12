#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include "dyn_alloc.h"

int		main(void)
{
	// printf("%d", getpagesize());
	ft_malloc(1);
	return (0);
}
