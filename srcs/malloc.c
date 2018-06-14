#include "dyn_alloc.h"

t_base	g_bases = { NULL, NULL, NULL };

t_block	*extend_heap(size_t size, t_block *previous)
{
	t_block	*b;
	size_t	size_to_map;
	size_t	mmap_size;

	size_to_map = sizeof_header() + size;
	mmap_size = ((size_to_map  / page_size()) + 1) * page_size();
	ft_putendl("EXTEND HEAP");
	ft_putnbr2("Size needed = size + sizeof_header = ", size_to_map);
	ft_putnbr2("mmap_size = ", mmap_size);
	b = mmap(0, size_to_map, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	b->size = mmap_size - sizeof_header();
	if (size > b->size)
		ft_putendl("Extend size error !");
	b->status = FREE;
	b->next = NULL;
	if (previous)
		previous->next = b;
	return (b);
}

// t_block	*find_available_block(t_block *blocks, size_t size)
// {
// 	while (blocks)
// 	{
// 		if (blocks->size >= size)
// 			return (blocks);
// 		blocks = blocks->next;
// 	}
// 	return (NULL);
// }

t_block *find_available_or_last_block(t_block *blocks, size_t size)
{
	while (blocks)
	{
		if (blocks->size >= size)
			return (blocks);
		if (!blocks->next)
			break ;
		blocks = blocks->next;
	}
	return (blocks);
}

bool	is_available_block(t_block *block, size_t size)
{
	return (block->size >= size ? true : false);
}

t_block	*find_or_extend(t_block **blocks, size_t size)
{
	t_block		*place;

	if (!*blocks)
	{
		*blocks = extend_heap(size, *blocks);
		return(*blocks);
	}
	place = find_available_or_last_block(*blocks, size);
	if (is_available_block(place, size) == true)
		return (place);
	else
		return (extend_heap(size, place));
}

// t_block	*split_block(t_block *block, size_t size)
// {
// 	t_block		*new_block;

// 	new_block = (unsigned char *)
// 	block->size = size;
// }

void	display_all_blocks(t_block *blocks)
{
	int		i;

	ft_putendl("DISPLAY ALL BLOCKS :");
	i = 1;
	while (blocks)
	{
		ft_putnbr2("i = ", i);
		ft_putstr("address = ");
		ft_display_addr((unsigned long long)blocks);
		ft_putnbr2("size of header = ", sizeof_header());
		ft_putnbr2("size of block (without header) = ", blocks->size);
		ft_putendl2("status = ", blocks->status == FREE ? "FREE" : "ALLOC");
		ft_putendl("---------");
		blocks = blocks->next;
		i++;
	}
}

void	*ft_malloc(size_t size)
{
	t_block		*alloc_b;

	ft_putnbr2("MALLOC - size ", size);
	if (!g_bases.tiny)
		ft_putendl("First init");
	else
		ft_putendl("Next init");
	alloc_b = find_or_extend(&g_bases.tiny, size);
	ft_putendl("");
	display_all_blocks(g_bases.tiny);
	ft_putendl("--- END MALLOC ------------------\n");

	return ((unsigned char *)alloc_b + sizeof_header());
}

// void	*ft_malloc(size_t size)
// {
// 	ft_putnbr2("MALLOC - size ", size);
// 	if (!g_bases.tiny)
// 	{
// 		ft_putendl("First init");
// 		g_bases.tiny = extend_heap(size, NULL);
// 	}
// 	else
// 	{
// 		ft_putendl("Next init");
// 		t_block *last = find_last_block(g_bases.tiny);
// 		extend_heap(size, last);
// 	}

// 	display_all_blocks(g_bases.tiny);
// 	ft_putendl("--- END MALLOC ------------------\n");

// 	return (g_bases.tiny);
// }

void	*malloc(size_t size)
{
	return (ft_malloc(size));
}
