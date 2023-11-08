#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int args, char* argv[])
{
    int input = open(argv[1], O_RDONLY);
    int digits = open(argv[2], O_WRONLY | O_CREAT, 0640);
    int other = open(argv[3], O_WRONLY | O_CREAT, 0640);

    ssize_t bytes_read;
    char in_byte;
    int output_FD;
    while ((bytes_read = read(input, &in_byte, sizeof(in_byte))) > 0) {
        if ('0' <= in_byte && in_byte <= '9') {
            output_FD = digits;
        } else {
            output_FD = other;
        }
        write(output_FD, &in_byte, sizeof(in_byte));
    }
    return 0;
}