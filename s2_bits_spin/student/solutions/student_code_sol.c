#include"student_code_sol.h"

uint32_t cycle_bits_sol(uint32_t x, uint8_t n)
{
	return (x<<n%32)+(x>>(32-n%32));
}
