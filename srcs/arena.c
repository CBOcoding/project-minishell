#include "arena.h"
#include <string.h>

t_arena	*arena_create(size_t size)
{
	t_arena	*arena;

	arena = (t_arena *)malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->memory = (char *)malloc(size);
	if (!arena->memory)
	{
		free(arena);
		return (NULL);
	}
	arena->used = 0;
	arena->capacity = size;
	return (arena);
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	void	*ptr;

	if (!arena || arena->used + size > arena->capacity)
		return (NULL);
	ptr = arena->memory + arena->used;
	arena->used += size;
	return (ptr);
}

void	arena_reset(t_arena *arena)
{
	if (arena)
		arena->used = 0;
}

void	arena_destroy(t_arena *arena)
{
	if (arena)
	{
		free(arena->memory);
		free(arena);
	}
}
