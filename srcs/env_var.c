#include "dyn_alloc.h"

void	env_var_initialization(void)
{
	if (g_zone.get_histo == 0)
	{
		g_zone.get_histo = 1;
		g_zone.histo = getenv(HISTO_ENV_VAR) ? 1 : 0;
	}
	g_zone.show_alloc_mem = 0; //debug
}
