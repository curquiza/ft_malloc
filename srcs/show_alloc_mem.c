#include "dyn_alloc.h"

static size_t display_blocks(t_block *blocks)
{
	char	*start;
	char	*end;
	size_t	total;

	total = 0;
	while (blocks)
	{
		if (g_zone.show_free || blocks->status == ALLOC)
		{
			start = (char *)blocks + sizeof_header();
			end = (char *)blocks + sizeof_header() + blocks->size;
			if (g_zone.show_free)
				ft_putstr(blocks->status == ALLOC ? "alloc\t" : "free\t");
			ft_putaddr((unsigned long long)start);
			ft_putstr(" - ");
			ft_putaddr((unsigned long long)end);
			ft_putstr(" : ");
			ft_put_sizet((size_t)(end - start));
			ft_putendl(" octets");
			if (blocks->status == ALLOC)
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

	pthread_mutex_lock(&g_mutex);
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
	pthread_mutex_unlock(&g_mutex);
}
