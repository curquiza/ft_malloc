#include "dyn_alloc.h"

static size_t display_blocks(t_block *blocks)
{
	unsigned long long	start;
	unsigned long long	end;
	size_t				total;

	total = 0;
	while (blocks)
	{
		if (blocks->status == ALLOC)
		{
			start = (unsigned long long)blocks + sizeof_header();
			end = (unsigned long long)blocks + sizeof_header() + blocks->size;
			ft_putaddr(start);
			ft_putstr(" - ");
			ft_putaddr(end);
			ft_putstr(" : ");
			ft_put_sizet((size_t)(end - start));
			ft_putendl(" octets");
			total += (size_t)(end - start);
		}
		blocks = blocks->next;
	}
	return (total);
}

static void	display_zone(t_block *blocks, size_t *total)
{
	if (blocks == NULL)
		ft_putendl("NONE");
	else
	{
		ft_putaddr((unsigned long long)blocks);
		ft_putstr("\n");
		*total = *total + display_blocks(blocks);
	}
}

void	show_alloc_mem(void)
{
	size_t		total;

	total = 0;
	ft_putstr("TINY : ");
	display_zone(g_zone.tiny, &total);
	ft_putstr("SMALL : ");
	display_zone(g_zone.small, &total);
	ft_putstr("LARGE : ");
	display_zone(g_zone.large, &total);
	ft_putstr("Total : ");
	ft_put_sizet(total);
	ft_putendl(" octets");
}
