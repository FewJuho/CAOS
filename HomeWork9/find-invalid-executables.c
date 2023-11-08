#include <fcntl.h>
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
    char* back_slash_n;
    char file[PATH_MAX];
    struct stat stat1;
    while (fgets(file, sizeof(file), stdin)) {
        back_slash_n = memchr(file, '\n', sizeof(file));
        if (back_slash_n) {
            *back_slash_n = '\0';
        }
        int new_fd = open(file, O_RDONLY);
        if (new_fd <= 0) {
            continue;
        }
        if (fstat(new_fd, &stat1) != -1) {
            if (stat1.st_mode & S_IXUSR) {
                if (lseek(new_fd, 0, SEEK_END) >= 2) {
                    lseek(new_fd, 0, SEEK_SET);
                    char first = 0;
                    char second = 0;
                    read(new_fd, &first, sizeof(char));
                    read(new_fd, &second, sizeof(char));

                    if (first != '#' || second != '!') {
                        lseek(new_fd, 0, SEEK_SET);
                        char a = 0;
                        char b = 0;
                        char c = 0;
                        char d = 0;
                        read(new_fd, &a, sizeof(char));
                        read(new_fd, &b, sizeof(char));
                        read(new_fd, &c, sizeof(char));
                        read(new_fd, &d, sizeof(char));
                        if (a != 0x7f || b != 'E' || c != 'L' || d != 'F') {
                            goto PUTS;
                        }
                        continue;
                    }

                    char buff[PATH_MAX];
                    read(new_fd, buff, sizeof(buff));
                    back_slash_n = memchr(buff, '\n', sizeof(buff));
                    if (back_slash_n) {
                        *back_slash_n = '\0';
                    }
                    struct stat stat2;
                    if (stat(buff, &stat2) == -1 ||
                        !(stat2.st_mode & S_IXUSR)) {
                        goto PUTS;
                    }
                } else {
                    goto PUTS;
                }
            }
            continue;
        }
        continue;
    PUTS:
        puts(file);
    }
    return 0;
}