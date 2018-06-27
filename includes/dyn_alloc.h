#ifndef DYN_ALLOC_H
# define DYN_ALLOC_H

# include <unistd.h> // attention
# include <sys/mman.h>
# include <stdio.h> // attention
# include <stdbool.h>
# include <stdlib.h> // attention ?
# include <assert.h> // attention

# define HEXA_BASE "0123456789ABCDEF"
# define DEF "\033[0m" // enlever
# define B_BLUE "\x1b[1;34m" // enlever
# define B_GREEN "\x1b[1;32m" // enlever
# define B_YELLOW "\x1b[1;33m" // enlever

# define TINY_MAX 352 // 10 pages allouées (avec headers)
# define SMALL_MAX 4096 // 101 pages allouées (avec headers) - peut etre prendre en compte le hearder -> 4096 - header ?
# define ZONE_ALLOC_NB 100

# define SHOW_MEM_FREE_ENV_VAR "SHOW_MEM_FREE"
# define DEBUG_ENV_VAR "ALLOC42_DEBUG"
// # define NOCOLOR_ENV_VAR "ALLOC42_NOCOLOR"

enum	e_status
{
	FREE,
	ALLOC
};

enum	e_type
{
	TINY,
	SMALL,
	LARGE
};

typedef struct	s_block
{
	enum e_status	status;
	size_t			size;
	struct s_block	*prev;
	struct s_block	*next;
}				t_block;

typedef struct	s_zone
{
	enum e_type	type;
	t_block		*tiny;
	t_block		*small;
	t_block		*large;
	t_block		**current;
	int			debug;
	int			get_debug;
	int			show_alloc_mem; //tmp
}				t_zone;

t_zone	g_zone;

/*
** TOOLS
*/
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_put_sizet(size_t n);
void	ft_putstr(char const *s);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl(char const *s);
void	ft_putaddr(unsigned long long int n);
void	ft_putaddr_fd(unsigned long long int n, int fd);

size_t	ft_strlen(const char *s);

size_t	get_aligned_size(size_t size, int multiple);
int		sizeof_header(void);
int		page_size(void);

void	init_debug(void);

// NON-OFFICIAL DEBUGING FUNCTION
void	ft_putnbr2(char *s, int nbr);
void	ft_putendl2(char *s1, char *s2);
void	ft_putaddr2(char *s, unsigned long long int n);
// void	ft_putendl2_fd(char *s1, char *s2, int fd);

/*
** MALLOC
*/
void	*malloc(size_t size);

/*
** FREE
*/
t_block	*find_block(void *ptr);
void	free_on(t_block *block);
void	free(void *ptr);

/*
** REALLOC
*/
void	*realloc(void *ptr, size_t size);

/*
** CALLOC
*/
void	*calloc(size_t count, size_t size);

/*
** SHOW ALLOC MEM
*/
void	show_alloc_mem(void);

/*
** DEBUG
*/
void	malloc_input_debug(size_t size, size_t aligned_size);
void	malloc_output_debug(t_block *b);
void	free_debug(void *ptr);
void	realloc_input_debug(void *ptr, size_t size);
void	realloc_free_debug(t_block *b);
void	realloc_call_debug(void);
void	realloc_enough_space_debug(char *new, size_t old_size, size_t new_size);
void	realloc_output_debug(char *new, size_t old_size, size_t new_size);

#endif
