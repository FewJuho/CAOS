#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void fill(int** ptr, int64_t size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ptr[i][j] = -1;
        }
    }
    if (size == 1) {
        ptr[0][0] = 1;
        return;
    }
    int x = 0;
    int y = 0;
    int curr = 1;
    while (1) {
        while (x < size) {
            if (curr == size * size + 1) {
                goto end;
            }
            if (ptr[y][x] != -1) {
                break;
            }
            ptr[y][x] = curr;
            ++curr;
            ++x;
        }
        --x;
        ++y;
        while (y < size) {
            if (curr == size * size + 1) {
                goto end;
            }
            if (ptr[y][x] != -1) {
                break;
            }
            ptr[y][x] = curr;
            ++curr;
            ++y;
        }
        --y;
        --x;
        while (x > -1) {
            if (curr == size * size + 1) {
                goto end;
            }
            if (ptr[y][x] != -1) {
                break;
            }
            ptr[y][x] = curr;
            ++curr;
            --x;
        }
        ++x;
        --y;
        while (y > -1) {
            if (curr == size * size + 1) {
                goto end;
            }
            if (ptr[y][x] != -1) {
                break;
            }
            ptr[y][x] = curr;
            ++curr;
            --y;
        }
        ++y;
        ++x;
    }
end:
    ++x;
}

int main(int args, char* argv[])
{
    char* name = argv[1];
    int64_t size = strtol(argv[2], 0, 10);
    int64_t width = strtol(argv[3], 0, 10);
    int64_t file_size = (size * size * width + size - 1) * sizeof(char);
    int fd = open(name, O_CREAT | O_RDWR);
    if (fd < 0) {
        return 1;
    }
    lseek(fd, file_size - 1, SEEK_SET);
    write(fd, "", 1);
    lseek(fd, 0, SEEK_SET);

    int** numbers = (int**)malloc(sizeof(int*) * size);
    for (int i = 0; i < size; ++i) {
        numbers[i] = (int*)malloc(sizeof(int) * size);
    }
    fill(numbers, size);

    void* mmap_ptr =
        mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    char* copy = (char*)mmap_ptr;

    char format[100];
    format[0] = '%';
    int len = sprintf(format + 1, "%li", width);
    format[len + 1] = 'l';
    format[len + 2] = 'i';
    format[len + 3] = '\0';

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            sprintf(copy, format, numbers[i][j]);
            copy += width * sizeof(char);
        }
        if (i != size - 1) {
            sprintf(copy, "%c", '\n');
            copy += sizeof(char);
        }
    }

    close(fd);
    munmap(mmap_ptr, file_size);
    for (int i = 0; i < size; ++i) {
        free(numbers[i]);
    }
    free(numbers);
    return 0;
}
