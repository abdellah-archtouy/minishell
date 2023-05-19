#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

int main() {
	char command[MAX_COMMAND_LENGTH];

	while (1) {
		printf("Enter a command: ");
		fgets(command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = '\0'; // remove the trailing newline

		if (strcmp(command, "cd") == 0) {
			printf("Usage: cd <directory>\n");
		} else if (strncmp(command, "cd ", 3) == 0) {
			char* directory = command + 3; // skip the "cd " part

			if (chdir(directory) == 0) {
				printf("Directory changed to %s\n", directory);
			} else {
				printf("Failed to change directory to %s\n", directory);
			}
		} else if (strcmp(command, "exit") == 0) {
			break;
		} else {
			printf("Unknown command: %s\n", command);
		}
	}

	return 0;
}
