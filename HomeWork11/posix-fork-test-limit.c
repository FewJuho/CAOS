#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int count = 1;
    pid_t pid = 0;
    int start_pid = getpid();
    while (getpid() == start_pid) {
        if (-1 == (pid = fork())) {
            break;
        }
        ++count;
    }

    pid = waitpid(pid, 0, 0);
    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else if (pid == -1){
        printf("%i", count);
    }
    return 0;
}