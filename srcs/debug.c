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
	// !getenv(NOCOLOR_ENV_VAR) ? ft_putstr_fd(B_BLUE, 2) : 0;
	ft_putstr_fd("MALLOC", 2);
	// !getenv(NOCOLOR_ENV_VAR) ? ft_putstr_fd(DEF, 2) : 0;
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
	// !getenv(NOCOLOR_ENV_VAR) ? ft_putstr_fd(B_GREEN, 2) : 0;
	ft_putstr_fd("FREE", 2);
	// !getenv(NOCOLOR_ENV_VAR) ? ft_putstr_fd(DEF, 2) : 0;
	ft_putstr_fd("\t\tinput address : ", 2);
	ft_putaddr_fd((unsigned long long)ptr, 2);
	ft_putstr_fd("\n", 2);
}

void	realloc_input_debug(void *ptr, size_t size)
{
	// !getenv(NOCOLOR_ENV_VAR) ? ft_putstr_fd(B_YELLOW, 2) : 0;
	ft_putstr_fd("REALLOC", 2);
	// !getenv(NOCOLOR_ENV_VAR) ? ft_putstr_fd(DEF, 2) : 0;
	ft_putstr_fd("\t\tinput size : ", 2);
	ft_putnbr_fd(size, 2);
	ft_putstr_fd(" - input address : ", 2);
	ptr ? ft_putaddr_fd((unsigned long long)ptr, 2) : ft_putstr_fd("NULL", 2);
	ft_putstr_fd("\n", 2);
}

void	realloc_call_debug(void)
{
	ft_putstr_fd("  >> in realloc : ", 2);
}

void	realloc_free_debug(t_block *b)
{
	realloc_call_debug();
	free_debug((char *)b + sizeof_header());
}

static void	realloc_rslt_debug(char *new, size_t old_size, size_t new_size)
{
	ft_putstr("sizes : ");
	ft_put_sizet(old_size);
	ft_putstr(" -> ");
	ft_put_sizet(new_size);
	ft_putstr(" - ");
	ft_putstr("return value = ");
	ft_putaddr((unsigned long long)new);
	ft_putstr("\n");
}

void	realloc_enough_space_debug(char *new, size_t old_size, size_t new_size)
{
	realloc_call_debug();
	ft_putstr("ENOUGH SPACE - ");
	realloc_rslt_debug(new, old_size, new_size);
}

void	realloc_output_debug(char *new, size_t old_size, size_t new_size)
{
	realloc_call_debug();
	realloc_rslt_debug(new, old_size, new_size);
}
