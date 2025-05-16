// arena_utils.c
#include "arena.h"
#include <string.h>

// Copia una stringa usando arena_alloc()
char	*arena_strdup(t_arena *arena, const char *src)
{
	size_t	len;
	char	*dest;

	len = strlen(src) + 1;
	dest = (char *)arena_alloc(arena, len);
	if (!dest)
		return (NULL);
	strcpy(dest, src);
	return (dest);
}

// Concatena due stringhe e alloca nella arena
char	*arena_strjoin(t_arena *arena, const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	len1 = strlen(s1);
	len2 = strlen(s2);
	joined = (char *)arena_alloc(arena, len1 + len2 + 1);
	if (!joined)
		return (NULL);
	strcpy(joined, s1);
	strcat(joined, s2);
	return (joined);
}

// Crea una sottostringa e alloca nella arena
char	*arena_substr(t_arena *arena, const char *s, size_t start, size_t len)
{
	size_t	slen;
	char	*sub;

	slen = strlen(s);
	if (start >= slen)
		return (arena_strdup(arena, ""));
	if (start + len > slen)
		len = slen - start;
	sub = (char *)arena_alloc(arena, len + 1);
	if (!sub)
		return (NULL);
	strncpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
