#include <stdlib.h>
#include <stdio.h>

int		main(void)
{
	char	*a;
	int		i;

	a = (char *)malloc(10);
	i = 0;
	while (i < 10)
	{
		a[i] = 'c';
		i++;
	}
	//free(a + 1); // breakpoint malloc
	//free(a - 1); // breakpoint malloc
	free(a); //ok
}
