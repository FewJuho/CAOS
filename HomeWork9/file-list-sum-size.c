#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int64_t summary = 0;
    char file[PATH_MAX + 1];
    struct stat stat;
    while (fgets(file, sizeof(file), stdin)) {
        char* back_slash_n = memchr(file, '\n', sizeof(file));
        if (back_slash_n != 0) {
            *back_slash_n = '\0';
        }
        if (lstat(file, &stat) != -1) {
            if (S_ISREG(stat.st_mode)) {
                summary += stat.st_size;
            }
        }
    }
    printf("%li", summary);
}