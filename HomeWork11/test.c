#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int count = 0;
    int pid = 0;
    int start_pid = getpid();
    while (getpid() == start_pid) {
        if (-1 == (pid = fork())) {
            break;
        }
        ++count;
    }
    if (getpid() == start_pid) {
        printf("%i", count + 1);
    }
    return 0;
}