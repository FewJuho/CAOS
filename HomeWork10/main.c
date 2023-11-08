#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int curr = 0;
    int max = 10;
    while (curr < max) {
        ++curr;
        printf("%i ", curr);
        int k = fork();
        if (k != 0) {
            break;
        }
    }
    return 0;
}