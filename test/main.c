# include "../includes/malloc.h"

int main(void)
{
	char *str;

	str = malloc(1024 * 1000);
	realloc(str, sizeof(char *) * 313);
	show_alloc_mem();
	return 0;
}
