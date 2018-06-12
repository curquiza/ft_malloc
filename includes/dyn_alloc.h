#ifndef DYN_ALLOC_H
# define DYN_ALLOC_H

# include <unistd.h>
# include <sys/mman.h>
// # include <stdlib.h>
# include <stdio.h>

/*
** TOOLS
*/
void	ft_putnbr(int n);
void	ft_putnbr2(char *s, int nbr);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl2_fd(char *s1, char *s2, int fd);

size_t	ft_strlen(const char *s);

/*
** MALLOC
*/
void	*ft_malloc(size_t size);
void	*malloc(size_t size);

#endif