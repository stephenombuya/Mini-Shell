#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void display_prompt() {
    printf("mini-shell> ");
    fflush(stdout);
}

void execute_command(char *input) {
    char *args[MAX_ARGS];
    int i = 0;

    // Tokenize the input string into arguments
    char *token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Null-terminate the argument list

    if (args[0] == NULL) {
        return; // Empty input
    }

    if (strcmp(args[0], "exit") == 0) {
        exit(0); // Exit the shell
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) < 0) {
            perror("Command execution failed");
        }
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input[MAX_INPUT];

    while (1) {
        display_prompt();

        // Read input from the user
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break; // Exit on EOF
        }

        // Remove the newline character
        input[strcspn(input, "\n")] = 0;

        execute_command(input);
    }

    printf("\nExiting mini-shell. Goodbye!\n");
    return 0;
}
