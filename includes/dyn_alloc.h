#ifndef DYN_ALLOC_H
# define DYN_ALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdbool.h>

# define LITTLE_HEXA_BASE "0123456789abcdef"

enum	e_status
{
	FREE,
	ALLOC
};

typedef struct	s_block
{
	enum e_status	status;
	size_t			size;
	struct s_block	*next;
}				t_block;

typedef struct	s_base
{
	t_block	*tiny;
	t_block	*small;
	t_block	*large;
}				t_base;

/*
** TOOLS
*/
void	ft_putnbr(int n);
void	ft_putnbr2(char *s, int nbr);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putendl2(char *s1, char *s2);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl2_fd(char *s1, char *s2, int fd);
void	ft_display_addr(unsigned long long int n);
void	ft_display_hex_byte(unsigned char c);

size_t	ft_strlen(const char *s);

int		sizeof_header(void);
int		page_size(void);

/*
** MALLOC
*/
void	*ft_malloc(size_t size);
void	*malloc(size_t size);

#endif