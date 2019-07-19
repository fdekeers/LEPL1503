#include "student_code_sol.h"
uint8_t nbits_sol(uint32_t n)
{
	uint8_t ret = 0;
	//ret = 1; //fait échouer nbits
	for (;n; n = n>>1)
		if (n&1)
			ret++;
	return ret;

}
