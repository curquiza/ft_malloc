#include "dyn_alloc.h"

static t_block	*look_for_addr_on(t_block *blocks, void *ptr)
{
	while (blocks)
	{
		if ((unsigned char *)blocks + sizeof_header() == (unsigned char *)ptr)
			return (blocks);
		blocks = blocks->next;
	}
	return (NULL);
}

static void	free_on(t_block *block)
{
	(void)block;
}

void	free(void *ptr)
{
	t_block		*b_to_free;

	ft_putstr(B_GREEN"FREE"DEF" - addr : ");
	ft_display_addr((unsigned long long)ptr);
	ft_putstr("\n");
	
	if (ptr == NULL)
		return ;
	b_to_free = look_for_addr_on(g_zone.large, ptr);
	if (b_to_free == NULL)
	{
		b_to_free = look_for_addr_on(g_zone.small, ptr);
		if (b_to_free == NULL)
		{
			b_to_free = look_for_addr_on(g_zone.tiny, ptr);
			if (b_to_free == NULL)
			{
				ft_putendl("FREE ABORT"); // abort()
				return ;
			}
		}
	}
	free_on(b_to_free);
}
