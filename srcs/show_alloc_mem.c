#include "dyn_alloc.h"

static void	show_status(t_block *b)
{
	if (b->status == ALLOC)
		ft_putstr("alloc\t");
	else if (b->status == FREE)
		ft_putstr("free\t");
	else
		ft_putstr("KO\t");
}

static size_t display_blocks(t_block *blocks)
{
	char	*start;
	char	*end;
	size_t				total;

	total = 0;
	while (blocks)
	{
		// if (blocks->status == ALLOC || getenv(SHOW_MEM_FREE_ENV_VAR))
		// {
			start = (char *)blocks + sizeof_header();
			end = (char *)blocks + sizeof_header() + blocks->size;
			// getenv(SHOW_MEM_FREE_ENV_VAR) ? show_status(blocks) : 0;
			show_status(blocks);
			ft_putaddr((unsigned long long)start);
			ft_putstr(" - ");
			ft_putaddr((unsigned long long)end);
			ft_putstr(" : ");
			ft_put_sizet((size_t)(end - start));
			if (g_zone.histo == 1)
			{
				ft_putstr(" octets - prev : ");
				ft_putaddr((unsigned long long)blocks->prev);
				ft_putstr(" - next : ");
				ft_putaddr((unsigned long long)blocks->next);
				ft_putstr(" - block : ");
				ft_putaddr((unsigned long long)blocks);
				ft_putendl("");
			}
			else
				ft_putendl(" octets");
			if (blocks->status == ALLOC)
				total += (size_t)(end - start);
		// }
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
