/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:17 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/24 14:56:40 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define PROT PROT_READ | PROT_WRITE
# define MAP MAP_ANON | MAP_PRIVATE

# define DEBUG 0

# define T_BLOCK_SIZE sizeof(size_t)
# define T_ZONE_SIZE sizeof(t_zone)

# define VAL(X) *(size_t *)X

# define PAGE_SIZE sysconf(_SC_PAGESIZE)

typedef enum		e_zone_type
{
	TINY = 1024,
	SMALL = 4094 * 16,
	LARGE = -1
}					t_zone_type;

typedef struct		s_zone
{
	struct s_zone	*next;
	t_zone_type		type;
	size_t			nb_blocks;
	size_t			nb_max_blocks;
	size_t			zone_length;
}					t_zone;

typedef struct		s_mem
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
}					t_mem;

/*
** MAIN
*/

void				free(void *ptr);
void				*realloc(void *ptr, size_t size);

/*
** MALLOC.C
*/

void				*malloc(size_t size);
t_zone				*create_zone(size_t size);
void				zone_addend(t_zone **alst, t_zone *new);
t_zone				*add_zone(size_t size);
void				init_all_blocks(t_zone **zone);

/*
** SHOW.C
*/

void				show_alloc_mem(void);
int					show_alloc_mem_test(void);

/*
** TOOLS.C
*/

void				*smmap(size_t len);
int					optim_nb_block(size_t len);
t_zone				**get_zones(void);
int					zone_size_by_size(size_t size);
t_zone_type			zone_type(size_t size);
size_t				calculate(size_t nb, size_t size);
void				free_block(t_zone **z, void *ptr);
void				copy_blocks(void *old,
						size_t old_size, void *new, size_t new_size);

/*
** PRINT.C
*/

void				ft_puthex(void *ptr);
void				ft_putnbr(int n);
void				ft_putuint(size_t n);
void				ft_putstr(char const *s);

#endif
