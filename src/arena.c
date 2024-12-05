/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:13:38 by ozdemir           #+#    #+#             */
/*   Updated: 2024/12/05 17:20:40 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    arena_init(t_arena *arena, size_t size)
{
        arena->memory = malloc(size);
        if (!arena->memory)
        {
                printf("Error: arena malloc failed\n");
                return ;
        }
        arena->used = 0;
        arena->size = size;
}

void    free_arena(t_arena *arena)
{
        free(arena->memory);
        arena->memory = NULL;
        arena->used = 0;
        arena->size = 0;
}

void    *arena_alloc(t_arena *arena, size_t size)
{
        void    *ptr;
        if (arena->used + size > arena->size)
                return (NULL);
        ptr = arena->memory + arena->used;
        arena->used += size;
        ft_memset(ptr, 0, sizeof(size));
        return (ptr);
}