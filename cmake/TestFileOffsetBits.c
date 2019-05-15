// From https://github.com/Framstag/libosmscout/pull/251/files#diff-40f8e3cdfc36152528d5235258332447
#include <sys/types.h>

/* Cause a compile-time error if off_t is smaller than 64 bits */
#define LARGE_OFF_T (((off_t) 1 << 62) - 1 + ((off_t) 1 << 62))
int off_t_is_large[ (LARGE_OFF_T % 2147483629 == 721 && LARGE_OFF_T % 2147483647 == 1) ? 1 : -1 ];

int main(int argc, char **argv)
{
	(void) argc; (void) argv;
	return 0;
}
