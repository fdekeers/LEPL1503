#include"student_code_sol.h"

uint32_t unset_strong_bit_sol(uint32_t x)
{
	if (!x)
		return 0;
	for (short i = 1; i<32; i++)
		if (!(x>>i))
			return x - (1<<(i-1));
	return x;
}
