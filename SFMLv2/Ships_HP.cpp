#include "Ships_HP.h"


bool Ships_HP::chceckhp()
{
	if (size_5 || size_4 || size_3 || size_2 || size_ir2 || size_ir3)
		return true;
	return false;
}