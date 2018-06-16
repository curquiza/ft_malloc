#include "dyn_alloc.h"

t_zone	g_zone = { TINY, NULL, NULL, NULL, &g_zone.tiny };

t_block	*extend_heap(size_t size, t_block *previous)
{
	t_block	*b;
	size_t	size_to_map;
	size_t	mmap_size;

	size_to_map = sizeof_header() + size;
	mmap_size = ((size_to_map  / page_size()) + 1) * page_size();
	// ft_putendl("EXTEND HEAP"); // debug
	// ft_putnbr2("Size needed = size + sizeof_header = ", size_to_map); // debug
	// ft_putnbr2("mmap_size = ", mmap_size); // debug
	b = mmap(0, size_to_map, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	b->size = mmap_size - sizeof_header();
	// if (size > b->size) // debug
		// ft_putendl("Extend size error !"); // debug
	b->status = FREE;
	b->next = NULL;
	if (previous)
		previous->next = b;
	return (b);
}

t_block *find_available_or_last_block(t_block *blocks, size_t size)
{
	while (blocks)
	{
		if (blocks->size >= size && blocks->status == FREE)
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

t_block	*split_block(t_block *block, size_t size)
{
	t_block		*new_block;
	size_t		total_size;

	total_size = block->size + sizeof_header();
	new_block = (t_block *)((unsigned char *)block + sizeof_header() + size);
	new_block->size = total_size - size - sizeof_header() * 2;
	new_block->status = FREE;
	new_block->next = block->next;
	block->size = size;
	// block->status = ALLOC;
	block->next = new_block;
	return(block);
}

void	display_all_blocks(t_block *blocks) // debug
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
		ft_putnbr2("size totale = ", blocks->size + sizeof_header());
		ft_putendl2("status = ", blocks->status == FREE ? "FREE" : "ALLOC");
		ft_putendl("---------");
		blocks = blocks->next;
		i++;
	}
}

void	allocate_block(t_block *block, size_t size)
{
	if (block->size > size + sizeof_header()) //j'ai la place de mettre un header si je split
		split_block(block, size);
	block->status = ALLOC;
	// if (size > block->size) // debug
		// ft_putendl("Split size error"); // debug
}

void	type_initialization(size_t size)
{
	if (size <= TINY_MAX)
	{
		ft_putendl("TINY"); // debug
		g_zone.type = TINY;
		g_zone.current = &g_zone.tiny;
	}
	else if (size <= SMALL_MAX)
	{
		ft_putendl("SMALL"); // debug
		g_zone.type = SMALL;
		g_zone.current = &g_zone.small;
	}
	else
	{
		ft_putendl("LARGE"); // debug
		g_zone.type = LARGE;
		g_zone.current = &g_zone.large;
	}
}

void	*malloc(size_t size)
{
	t_block		*alloc_b;

	if ((int)size < 0)
		return (NULL);
	ft_putnbr2(B_BLUE"MALLOC"DEF" - size ", size); // debug
	type_initialization(size);
	// ft_putendl(!g_zone.current ? "First init" : "Next init"); // debug
	alloc_b = find_or_extend(g_zone.current, size);
	allocate_block(alloc_b, size);
	ft_putendl(""); // debug
	display_all_blocks(*g_zone.current); // debug
	ft_putendl("--- END MALLOC ------------------\n"); // debug

	return ((unsigned char *)alloc_b + sizeof_header());
}
