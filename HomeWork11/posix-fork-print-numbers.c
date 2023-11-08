#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int32_t N = strtol(argv[1], NULL, 10);
    for (int32_t i = 1; i <= N; i++) {
        if (fork() == 0) {
            printf("%u", i);
            if (i < N) {
                printf("%s", " ");
                exit(0);
            }
        }
        wait(0);
    }
}