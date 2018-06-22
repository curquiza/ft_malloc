#include "dyn_alloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}

size_t	get_aligned_size(size_t size, int multiple)
{
	if (size == 0)
		return (multiple);
	return ((size - 1) / multiple * multiple + multiple);
	// return ((((size - 1) >> 4) << 4) + 16);
}

int		sizeof_header(void)
{
	return (get_aligned_size(sizeof(t_block), 16));
}

int		page_size(void)
{
	return (getpagesize());
}
