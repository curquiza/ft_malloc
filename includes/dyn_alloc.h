/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_alloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:36:26 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/28 19:37:13 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYN_ALLOC_H
# define DYN_ALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>

# define HEXA_BASE "0123456789ABCDEF"

# define IMP_TO_FREE_MSG "  >> impossible to free this address.\n"
# define IMP_TO_REALLOC_MSG "  >> impossible to realloc this address.\n"

# define TINY_MAX 352
# define SMALL_MAX 4064
# define ZONE_ALLOC_NB 100

# define HISTO_ENV_VAR "ALLOC42_HISTO"
# define SHOW_FREE_ENV_VAR "ALLOC42_SHOW_FREE"

enum					e_status
{
	FREE,
	ALLOC
};

enum					e_type
{
	TINY,
	SMALL,
	LARGE
};

typedef struct			s_block
{
	enum e_status	status;
	size_t			size;
	struct s_block	*prev;
	struct s_block	*next;
}						t_block;

typedef struct			s_zone
{
	enum e_type	type;
	t_block		*tiny;
	t_block		*small;
	t_block		*large;
	t_block		**current;
	int			histo;
	int			get_histo;
	int			show_free;
	int			get_show_free;
}						t_zone;

t_zone					g_zone;
extern pthread_mutex_t	g_mutex;

/*
** TOOLS
*/
void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_put_sizet(size_t n);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl(char const *s);
void					ft_putaddr(unsigned long long int n);
void					ft_putaddr_fd(unsigned long long int n, int fd);

size_t					get_aligned_size(size_t size, int multiple);
int						sizeof_header(void);
int						page_size(void);

t_block					*find_block(void *ptr);

/*
** MALLOC
*/
t_block					*find_or_extend(t_block **blocks, size_t size);
void					*malloc(size_t size);

/*
** FREE
*/
void					free_on(t_block *block);
void					free(void *ptr);

/*
** REALLOC
*/
void					*realloc(void *ptr, size_t size);

/*
** CALLOC
*/
void					*calloc(size_t count, size_t size);

/*
** ENV VARIABLES
*/
void					env_var_initialization(void);

/*
** HISTO
*/
void					malloc_input_debug(size_t size, size_t aligned_size);
void					malloc_output_debug(t_block *b);
void					free_debug(void *ptr);
void					realloc_input_debug(void *ptr, size_t size);
void					realloc_free_debug(t_block *b);
void					realloc_call_debug(void);
void					realloc_enough_space_debug(void);
void					calloc_input_debug(size_t count, size_t size);
void					calloc_call_debug(void);

/*
** HEX DUMP
*/
void					hex_dump(void *addr, size_t size);

/*
** SHOW ALLOC MEM
*/
void					show_alloc_mem(void);
void					show_alloc_mem_hex(void);

#endif
