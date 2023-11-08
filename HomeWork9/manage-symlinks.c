#include <fcntl.h>
#include <inttypes.h>
#include <libgen.h>
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
    char file[PATH_MAX + 1];
    struct stat stat1;
    while (fgets(file, sizeof(file), stdin)) {
        back_slash_n = memchr(file, '\n', sizeof(file));
        if (back_slash_n != 0) {
            *back_slash_n = '\0';
        }

        if (lstat(file, &stat1) != -1) {
            if (S_ISREG(stat1.st_mode)) {
                char buff[PATH_MAX + 1];
                strcat(strcpy(buff, "link_to_"), basename(file));
                symlink(file, buff);
                continue;
            }

            if (S_ISLNK(stat1.st_mode)) {
                char file_name[PATH_MAX + 1];
                char path_name[PATH_MAX + 1];
                char buff[PATH_MAX + 1];
                buff[readlink(file, buff, sizeof(buff))] = '\0';
                strcpy(file_name, dirname(file));
                strcat(file_name, "/");
                strcat(file_name, buff);
                realpath(file_name, path_name);
                puts(path_name);
            }
        }
    }
}