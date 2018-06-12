#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int		main(void)
{
	printf("%d", getpagesize());
	return (0);
}
