#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    long long sum = 0;
    for (int i = 1; i < argc; i++) {
        char* q = argv[i];
        if (atoll(q)) {
            sum += (atoll(argv[i]));
        } else {
            printf("%s", q);
            printf("\n");
        }
    }
    printf("%lld", sum);
}


