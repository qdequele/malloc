/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/12 14:58:27 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <malloc.h>


void	*smmap(size_t len)
{
	return mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

void	*malloc(size_t size) {

}

int		main(int argc, char **argv)
{
	return 0
}