#include "dyn_alloc.h"

void	env_var_initialization(void)
{
	if (g_zone.get_histo == 0)
	{
		g_zone.get_histo = 1;
		g_zone.histo = getenv(HISTO_ENV_VAR) ? 1 : 0;
	}
	if (g_zone.get_show_free == 0)
	{
		g_zone.get_show_free = 1;
		g_zone.show_free = getenv(SHOW_FREE_ENV_VAR) ? 1 : 0;
	}
}
