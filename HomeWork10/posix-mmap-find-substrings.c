#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char* str_to_find = argv[2];
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        return 0;
    }
    struct stat st;
    fstat(fd, &st);
    if (st.st_size == 0) {
        return 0;
    }
    char* mmap_begin = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    char* mmap_iterator = mmap_begin;
    int64_t len = st.st_size;
    while ((mmap_iterator =
                memmem(mmap_iterator, len, str_to_find, strlen(str_to_find))) !=
           NULL) {
        int64_t diff = mmap_iterator - mmap_begin;
        len = (int64_t)st.st_size - diff;
        printf("%li ", diff);
        mmap_iterator++;
    }
    munmap(mmap_begin, st.st_size);
    close(fd);
    return 0;
}
