#include "stdafx.h"
#include "stack.h"

bool array_s::add_stack(stack & s)
{
	bool f = !full();
	if (f)
	{
		s.begin = s.end = beg_end[cur_numb_of_stack++].first;
	}
	return f;
}
