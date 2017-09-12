/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:17 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/12 17:45:38 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# include <sys/mman.h>

# define TINY_SIZE 10
# define SMALL_SIZE 128
# define PAGE_SIZE 

typedef enum	e_zone_type
{
	TINY,
	SMALL,
	LARGE
}				t_zone_type;

typedef struct	s_block
{
	void		*ptr;
	size_t		size;
	int			is_free;
	s_block		*next;
}				t_block;

typedef struct s_zone
{
	size_t		size;
	t_zone_type	type;
	s_zone		*next;
	t_block		*blocks;
	size_t		nb_blocks;
}				t_zone;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem();

#endif
