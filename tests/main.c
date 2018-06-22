#include <stdlib.h>
#include <stdio.h>

// int		main(void)
// {
// 	char	*a;
// 	int		i;

// 	a = (char *)malloc(10);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		a[i] = 'c';
// 		i++;
// 	}
// 	//free(a + 1); // breakpoint malloc
// 	//free(a - 1); // breakpoint malloc
// 	free(a); //ok
// }

int		main(void)
{
	char	*a;
	char	*b;
	int		i;

	a = (char *)malloc(10);
	i = 0;
	while (i < 10)
	{
		a[i] = 'c';
		i++;
	}
	printf("a avant realloc = %p\n", a);	
	// b = realloc(a, 16);
	b = realloc(a, 20);
	printf("a apres realloc = %p\n", a);
	printf("afficher a = %s\n", a);
	printf("b = %p\n", b);
	printf("afficher b = %s\n", b);
}
