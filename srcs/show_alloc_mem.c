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
			ft_display_addr_noendl(start);
			ft_putstr(" - ");
			ft_display_addr_noendl(end);
			ft_putstr(" : ");
			ft_putnbr(end - start);
			ft_putendl(" octets");
		}
		blocks = blocks->next;
	}
}

static void	display_tinies(void)
{
	ft_putstr("TINY : ");
	if (g_zone.tiny == NULL)
		ft_putendl("NONE");
	else
		ft_display_addr((unsigned long long)g_zone.tiny);
	display_blocks(g_zone.tiny);
}

static void	display_smalls(void)
{
	ft_putstr("SMALL : ");
	if (g_zone.small == NULL)
		ft_putendl("NONE");
	else
		ft_display_addr((unsigned long long)g_zone.small);
	display_blocks(g_zone.small);
}

static void	display_larges(void)
{
	ft_putstr("LARGES : ");
	if (g_zone.large == NULL)
		ft_putendl("NONE");
	else
		ft_display_addr((unsigned long long)g_zone.large);
	display_blocks(g_zone.large);
}

void	show_alloc_mem(void)
{
	display_tinies();
	display_smalls();
	display_larges();
}