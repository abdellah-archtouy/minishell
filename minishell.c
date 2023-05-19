#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void custom_action() {
	printf("Custom action performed.\n");
}

int	main()
{
	char	*input;
	char	*env[] = {NULL};

	while (1)
	{
		// Read a line of text
		input = readline("Enter a line: ");

		// Check if input is NULL (e.g., user pressed Ctrl+D)
		if (input == NULL)
		{
			printf("No input received.\n");
			return 1;
		}
		printf("You entered: %s\n", input);
		*env = getenv("PATH");
		execve("/bin/ls", &input, env);
		// Add the input to the history
		add_history(input);

		// Perform custom action after the user presses Enter
		rl_on_new_line();
		custom_action();

		// Free the memory allocated by readline
		free(input);
	}
	return 0;
}
