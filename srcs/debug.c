#include "dyn_alloc.h"

static void	put_type(void)
{
	if (g_zone.type == TINY)
		ft_putstr_fd(" TINY", 2);
	else if (g_zone.type == SMALL)
		ft_putstr_fd(" SMALL", 2);
	else
		ft_putstr_fd(" LARGE", 2);
}

void	malloc_input_debug(size_t size, size_t aligned_size)
{
	ft_putstr_fd(B_BLUE"MALLOC"DEF"", 2);
	put_type();
	ft_putstr_fd("\tinput size : ", 2);
	ft_putnbr_fd(size, 2);
	ft_putstr_fd(" - aligned size : ", 2);
	ft_putnbr_fd(aligned_size, 2);
}

void	malloc_output_debug(t_block *b)
{
	ft_putstr_fd(" - data address : ", 2);
	ft_putaddr_fd((unsigned long long)((char *)b + sizeof_header()), 2);
	ft_putstr_fd("\n", 2);
}

void	free_debug(void *ptr)
{
	ft_putstr_fd(B_GREEN"FREE"DEF"\t\tinput address : ", 2);
	ft_putaddr_fd((unsigned long long)ptr, 2);
	ft_putstr_fd("\n", 2);
}
