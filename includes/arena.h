#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>

# define ARENA_SIZE (64 * 1024)

typedef struct s_arena
{
	char *memory;    // Puntatore al blocco di memoria allocato
	size_t used;     // Quantità di memoria già usata
	size_t capacity; // Capacità totale dell'arena
}		t_arena;

// Crea una nuova arena con memoria di dimensione `size`
t_arena	*arena_create(size_t size);

// Alloca `size` byte nella memoria dell'arena
void	*arena_alloc(t_arena *arena, size_t size);

// Resetta l’arena per riutilizzarla da capo
void	arena_reset(t_arena *arena);

// Libera tutta la memoria associata all’arena
void	arena_destroy(t_arena *arena);

#endif
