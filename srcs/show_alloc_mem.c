#include "dyn_alloc.h"

static void display_blocks(t_block *blocks)
{
	unsigned long long	start;
	unsigned long long	end;

	while (blocks)
	{
		if (blocks->status == ALLOC)
		{
			start = (unsigned long long)blocks + sizeof_header();
			end = (unsigned long long)blocks + sizeof_header() + blocks->size;
			ft_display_addr(start);
			ft_putstr(" - ");
			ft_display_addr(end);
			ft_putstr(" : ");
			ft_putnbr(end - start);
			ft_putendl(" octets");
		}
		blocks = blocks->next;
	}
}

static void	display_zone(t_block *blocks)
{
	if (blocks == NULL)
		ft_putendl("NONE");
	else
	{
		ft_display_addr((unsigned long long)blocks);
		ft_putstr("\n");
		display_blocks(blocks);
	}
}

void	show_alloc_mem(void)
{
	ft_putstr("TINY : ");
	display_zone(g_zone.tiny);
	ft_putstr("SMALL : ");
	display_zone(g_zone.small);
	ft_putstr("LARGE : ");
	display_zone(g_zone.large);
}