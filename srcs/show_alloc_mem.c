#include "dyn_alloc.h"

// static void	show_status(t_block *b)
// {
// 	if (b->status == ALLOC)
// 		ft_putstr("alloc\t");
// 	else
// 		ft_putstr("alloc\t");
// }

// static size_t display_blocks(t_block *blocks)
// {
// 	char	*start;
// 	char	*end;
// 	size_t				total;

// 	total = 0;
// 	while (blocks)
// 	{
// 		// if (blocks->status == ALLOC || getenv(SHOW_MEM_FREE_ENV_VAR))
// 		// {
// 			start = (char *)blocks + sizeof_header();
// 			end = (char *)blocks + sizeof_header() + blocks->size;
// 			show_status(blocks);
// 			ft_putaddr((unsigned long long)start);
// 			ft_putstr(" - ");
// 			ft_putaddr((unsigned long long)end);
// 			ft_putstr(" : ");
// 			ft_put_sizet((size_t)(end - start));
// 			if (g_zone.histo == 1) //debug
// 			{ //debug
// 				ft_putstr(" octets - prev : "); //debug
// 				ft_putaddr((unsigned long long)blocks->prev); //debug
// 				ft_putstr(" - next : "); //debug
// 				ft_putaddr((unsigned long long)blocks->next); //debug
// 				ft_putstr(" - block : "); //debug
// 				ft_putaddr((unsigned long long)blocks); //debug
// 				ft_putendl(""); //debug
// 			} //debug
// 			else //debug
// 				ft_putendl(" octets");
// 			if (blocks->status == ALLOC)
// 				total += (size_t)(end - start);
// 		// }
// 		blocks = blocks->next;
// 	}
// 	return (total);
// }

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
