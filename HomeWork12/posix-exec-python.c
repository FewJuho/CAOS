#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char buff[4096];
    char str[4096];
    fgets(buff, sizeof(buff), stdin);
    char* slash = strchr(buff, '\n');
    if (slash)
        *slash = '\0';
    if (strnlen(buff, sizeof(buff)) == 0)
        return 0;
    snprintf(str, sizeof(str), "ans = %s; print(ans)", buff);
    execlp("python3", "python3", "-c", str, NULL);
    perror("failed to exec");
}