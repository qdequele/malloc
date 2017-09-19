/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:17 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/19 19:06:17 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define PROT PROT_READ | PROT_WRITE
# define MAP MAP_ANON | MAP_PRIVATE

# define TINY_SIZE 50
# define SMALL_SIZE 400
# define DEBUG 0

# define T_BLOCK_SIZE sizeof(size_t)
# define T_ZONE_SIZE sizeof(t_zone)
# define VAL(X) *(size_t *)X

# define TINY_ZONE_SIZE(X) (T_ZONE_SIZE + (X * T_BLOCK_SIZE) + (X * TINY_SIZE))
# define SMALL_ZONE_SIZE(X) (T_ZONE_SIZE + (X * T_BLOCK_SIZE) + (X * SMALL_SIZE))

# define ZONE_TYPE(SIZE) ((SIZE <= TINY_SIZE) ? TINY : (SIZE <= SMALL_SIZE) ? SMALL : LARGE)
# define ZONE_SIZE(TYPE) ((TYPE == TINY) ? TINY_SIZE : SMALL_SIZE)

# define PAGE_SIZE sysconf(_SC_PAGESIZE)

typedef enum		e_zone_type
{
	TINY,
	SMALL,
	LARGE
}					t_zone_type;

typedef struct		s_zone
{
	struct s_zone	*next;
	t_zone_type		type;
	size_t			nb_blocks;
	size_t			nb_max_blocks;
}					t_zone;

typedef struct		s_mem
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
}					t_mem;

// MAIN

void			free(void *ptr);
void			*realloc(void *ptr, size_t size);

// MALLOC.C

void			*malloc(size_t size);
t_zone			*create_zone(size_t size);
void			zone_addend(t_zone **alst, t_zone *new);
t_zone			*add_zone(size_t size);
void			init_all_blocks(t_zone **zone);

// SHOW.C

void			show_alloc_mem(void);

// TOOLS.C

void			*smmap(size_t len);
int				optim_nb_block(size_t len);
t_mem			*get_mem(void);
t_zone			**get_zones(size_t size);

#endif
