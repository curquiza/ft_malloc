#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int		main(void)
{
	printf("%d", getpagesize());		
	malloc(2);
	return (0);
}
