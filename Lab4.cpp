#include "Menu.h"

int main()
{
	int	f = 1;
	Menu menu;
	while (1)
	{
		if (f)
		{
			menu.log_check();
			f = 0;
		}
		menu.show();
		menu.ops();
	}
}

