#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char str[128];
    int p;
    int status_check = 1;
    pid_t start_pid = getpid();
    int* mmap_ptr = (int*)mmap(
        NULL,
        sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_SHARED,
        -1,
        0);
    while (status_check) {
        int input = scanf("%s", str);
        if (input == -1) {
            break;
        }
        p = fork();
        if (p != 0) {
            int status;
            waitpid(p, &status, 0);
            (*(mmap_ptr))++;
            break;
        }
    }

    if (getpid() == start_pid) {
        printf("%d", *mmap_ptr);
        munmap(mmap_ptr, sizeof(int));
    }
}