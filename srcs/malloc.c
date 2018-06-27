#include "dyn_alloc.h"

static size_t	get_extend_size(size_t size)
{
	size_t	s;

	if (g_zone.type == TINY)
		s = (TINY_MAX + sizeof_header()) * ZONE_ALLOC_NB;
	else if (g_zone.type == SMALL)
		s = (SMALL_MAX + sizeof_header()) * ZONE_ALLOC_NB;
	else
		s = size + sizeof_header();
	return (get_aligned_size(s, page_size()));
}

static t_block	*extend_heap(size_t size, t_block *previous)
{
	t_block	*b;
	size_t	mmap_size;

	mmap_size = get_extend_size(size);
	b = mmap(0, mmap_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->status = FREE;
	b->size = mmap_size - sizeof_header();
	// assert(size <= b->size);
	b->next = NULL;
	b->prev = previous;
	if (previous)
		previous->next = b;
	return (b);
}

static t_block *find_available_or_last_block(t_block *blocks, size_t size)
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
	return (block->size >= size && block->status == FREE ? true : false);
}

static t_block	*find_or_extend(t_block **blocks, size_t size)
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

static t_block	*split_block(t_block *block, size_t size)
{
	t_block		*new_block;
	t_block		*right;
	size_t		total_size;

	right = block->next;
	total_size = block->size + sizeof_header();
	new_block = (t_block *)((char *)block + sizeof_header() + size);
	new_block->size = total_size - size - sizeof_header() * 2;
	new_block->status = FREE;
	new_block->prev = block;
	new_block->next = block->next;
	block->size = size;
	block->next = new_block;
	if (right)
		right->prev = new_block;
	return (block);
}

// void	display_all_blocks(t_block *blocks)
// {
// 	int		i;
//
// 	ft_putendl("DISPLAY ALL BLOCKS :");
// 	i = 1;
// 	while (blocks)
// 	{
// 		ft_putnbr2("i = ", i);
// 		ft_putstr("address = ");
// 		ft_putaddr((unsigned long long)blocks);
// 		ft_putstr("\n");
// 		ft_putnbr2("size of header = ", sizeof_header());
// 		ft_putnbr2("size of block (without header) = ", blocks->size);
// 		ft_putnbr2("size totale = ", blocks->size + sizeof_header());
// 		ft_putendl2("status = ", blocks->status == FREE ? "FREE" : "ALLOC");
// 		ft_putendl("---------");
// 		blocks = blocks->next;
// 		i++;
// 	}
// }

static void	allocate_block(t_block *block, size_t size)
{
	if (g_zone.type != LARGE && block->size > size + sizeof_header()) //j'ai la place de mettre un header si je split
		split_block(block, size);
	block->status = ALLOC;
	// assert(size <= block->size);
}

static void	zone_type_initialization(size_t size)
{
	if (size <= TINY_MAX)
	{
		g_zone.type = TINY;
		g_zone.current = &g_zone.tiny;
	}
	else if (size <= SMALL_MAX)
	{
		g_zone.type = SMALL;
		g_zone.current = &g_zone.small;
	}
	else
	{
		g_zone.type = LARGE;
		g_zone.current = &g_zone.large;
	}
}

void	*malloc(size_t size)
{
	t_block		*alloc_b;
	size_t		new_size;

	init_debug();
	if ((int)size < 0)
		return (NULL);
	new_size = get_aligned_size(size, 16);
	zone_type_initialization(new_size);
	// getenv(DEBUG_ENV_VAR) ? malloc_input_debug(size, new_size) : 0;
	g_zone.debug ? malloc_input_debug(size, new_size) : 0;
	alloc_b = find_or_extend(g_zone.current, new_size);
	if (!alloc_b)
		return (NULL);
	allocate_block(alloc_b, new_size);
	// getenv(DEBUG_ENV_VAR) ? malloc_output_debug(alloc_b) : 0;
	g_zone.debug ? malloc_output_debug(alloc_b) : 0;
	if (g_zone.show_alloc_mem == 1)
	{
		ft_putstr("\n");
		show_alloc_mem();
		ft_putstr("\n");
	}
	return ((char *)alloc_b + sizeof_header());
}
