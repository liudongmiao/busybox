#include <string.h>

#ifdef __ANDROID__
void *mempcpy(void *dst, const void *src, int n)
{
	memcpy(dst, src, n);
	return ((char *)dst) + n;
}
#endif
