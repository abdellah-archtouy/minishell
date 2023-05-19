#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    fork();

    printf("current id %d || parent id %d\n", getpid(), getppid());
    return 0;
}