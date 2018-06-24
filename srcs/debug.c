#include "dyn_alloc.h"

void	malloc_input_debug(size_t size, size_t aligned_size)
{
	ft_putstr_fd(B_BLUE"MALLOC"DEF"", 2);
	ft_putstr_fd(" - input size = ", 2);
	ft_putnbr_fd(size, 2);
	ft_putstr_fd(" - aligned size = ", 2);
	ft_putnbr_fd(aligned_size, 2);
}

void	malloc_output_debug(t_block *b)
{
	ft_putstr_fd(" - data address : ", 2);
	ft_putaddr_fd((unsigned long long)((char *)b + sizeof_header()), 2);
	ft_putstr_fd("\n", 2);
}
