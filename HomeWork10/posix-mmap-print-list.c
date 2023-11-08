#include <dirent.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Item {
    int value;
    uint32_t next_pointer;
} item_t;

int main(int argc, char* argv[])
{
    struct stat st;
    char* file = argv[1];
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        return 1;
    }
    lstat(file, &st);
    if (st.st_size == 0) {
        return 2;
    }
    void* ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    item_t* item = (item_t*)ptr;
    printf("%d", item->value);
    while (item->next_pointer != 0) {
        item = (item_t*)(ptr + item->next_pointer);
        printf("%s", " ");
        printf("%d", item->value);
    }
    munmap(ptr, st.st_size);
    close(fd);
    return 0;
}