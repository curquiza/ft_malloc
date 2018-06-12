#include "dyn_alloc.h"

// void	*ft_malloc(size_t size)
void	*malloc(size_t size)
{
	char	*addr;

	ft_putnbr2("MALLOC - size ", size);
	addr = (char *)mmap(0, size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	printf("%p\n", addr);
	return ((void *)"coco");
}