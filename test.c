#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mini.h"


// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	int i;
// 	// pid_t pid = fork();
// 	char *args[] = {"/bin/cat", "a",NULL};
// 	// if (pid == 0)
// 	// {
// 		execve("/bin/catgvd", args, NULL);
// 	// }
// 	// waitpid(pid, &i, 0);
// 	printf("aa\n");
// 	// printf("aaaa\n");
// 	// pid_t pid1 = fork();
// 	// if (pid1 == 0)
// 	// {
// 	// 	execve("/bin/ls", args, NULL);
// 	// }
// 	// waitpid(pid1, &i, 0);
// }

#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = STDOUT_FILENO;  // File descriptor for standard output

    if (isatty(fd)) {
        printf("File descriptor %d is associated with a terminal\n", fd);
    } else {
        printf("File descriptor %d is not associated with a terminal\n", fd);
    }

    return 0;
}

