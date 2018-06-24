#ifndef DYN_ALLOC_H
# define DYN_ALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

# define LITTLE_HEXA_BASE "0123456789ABCDEF"
# define DEF "\033[0m"
# define B_BLUE "\x1b[1;34m"
# define B_GREEN "\x1b[1;32m"
# define B_YELLOW "\x1b[1;33m"

# define TINY_MAX 352 // 10 pages allouées (avec headers)
# define SMALL_MAX 4096 // 101 pages allouées (avec headers) - peut etre prendre en compte le hearder -> 4096 - header ?
# define ZONE_ALLOC_NB 100

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
}				t_zone;

t_zone	g_zone;

/*
** TOOLS
*/
void	ft_putnbr(int n);
void	ft_put_sizet(size_t n);
void	ft_putnbr2(char *s, int nbr);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putendl2(char *s1, char *s2);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl2_fd(char *s1, char *s2, int fd);
void	ft_display_addr(unsigned long long int n);
void	ft_display_addr_noendl(unsigned long long int n);
void	ft_display_hex_byte(unsigned char c);

size_t	ft_strlen(const char *s);

size_t	get_aligned_size(size_t size, int multiple);
int		sizeof_header(void);
int		page_size(void);

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
** SHOW ALLOC MEM
*/
void	show_alloc_mem(void);

#endif
