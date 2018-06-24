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
	// char	*c;
	int		i;

	a = (char *)malloc(8000);
	i = 0;
	while (i < 10)
	{
		a[i] = 'c';
		i++;
	}
	printf("a avant realloc = %p\n", a);
	// b = realloc(a, 16);
	b = realloc(a, 200);
	printf("a apres realloc = %p\n", a);
	printf("afficher a = %s\n", a);
	printf("b = %p\n", b);
	printf("afficher b = %s\n", b);

	// c = realloc(a, 20);
	// printf("c = %p\n", c);
	// printf("afficher a = %s\n", a); // des fois plante, des fois non
}
