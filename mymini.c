#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>


#define MAX_COMMAND_LENGTH 100

void readCommand(char* command) {
    printf(">> ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    // Remove newline character from the end
    command[strcspn(command, "\n")] = '\0';
    add_history(command);
     // strcspn returns the length of the initial segment of command which consists entirely of characters not in "\n"
}


void executeCommand(char* command) {
    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Parse the command into arguments
        char* args[MAX_COMMAND_LENGTH];
        char* token = strtok(command, " "); //
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Execute the command
        execvp(args[0], args);

        // If execvp returns, an error occurred
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process

        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            // printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        readCommand(command);
        executeCommand(command);
    }
    return 0;
}