#include <sys/syscall.h>
#include <sys/types.h>

long syscall(long number, ...);
void _start()
{
    char buffer[30000];
    size_t bytes = syscall(SYS_read, 0, buffer, 30000);
    syscall(SYS_write, 1, buffer, bytes);
    syscall(SYS_exit, 0);
}