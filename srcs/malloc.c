#include "dyn_alloc.h"

t_base	g_bases = { NULL, NULL, NULL };

t_block	*extend_heap(size_t size, t_block *previous)
{
	t_block	*b;

	b = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	b->size = (size / page_size()) * page_size() + page_size();
	b->status = FREE;
	b->next = NULL;
	if (previous)
		previous->next = b;
	return (b);
}

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
		ft_putnbr2("size of block = ", blocks->size);
		ft_putendl2("status = ", blocks->status == FREE ? "FREE" : "ALLOC");
		ft_putendl("---------");
		blocks = blocks->next;
		i++;
	}
}

t_block	*find_last_block(t_block *blocks)
{
	while (blocks && blocks->next)
		blocks = blocks->next;
	return (blocks);
}

void	*ft_malloc(size_t size)
{
	ft_putnbr2("MALLOC - size ", size);
	if (!g_bases.tiny)
	{
		ft_putendl("First init");
		g_bases.tiny = extend_heap(size, NULL);
	}
	else
	{
		ft_putendl("Next init");
		t_block *last = find_last_block(g_bases.tiny);
		if (last == NULL)
			ft_putendl("last est NULL");
		extend_heap(size, last);
	}

	display_all_blocks(g_bases.tiny);
	ft_putendl("--- END MALLOC ------------------\n");

	return (g_bases.tiny);
}

void	*malloc(size_t size)
{
	return (ft_malloc(size));
}
