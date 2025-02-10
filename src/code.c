#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void handle_signal(int sig) {
    printf("\nmini-shell> ");
    fflush(stdout);
}

void display_prompt() {
    printf("mini-shell> ");
    fflush(stdout);
}

void execute_command(char *input) {
    char *args[MAX_ARGS];
    int i = 0;
    int background = 0;
    int fd_in = 0, fd_out = 1;
    char *input_file = NULL, *output_file = NULL;

    // Tokenizing input while handling special characters
    char *token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        if (strcmp(token, "&") == 0) {
            background = 1;
        } else if (strcmp(token, "<") == 0) {
            input_file = strtok(NULL, " ");
        } else if (strcmp(token, ">") == 0) {
            output_file = strtok(NULL, " ");
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    // Built-in command: exit
    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting mini-shell.\n");
        exit(0);
    }

    // Built-in command: cd
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL || chdir(args[1]) != 0) {
            perror("cd failed");
        }
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        // Handle input redirection
        if (input_file) {
            fd_in = open(input_file, O_RDONLY);
            if (fd_in < 0) {
                perror("Input file open failed");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        // Handle output redirection
        if (output_file) {
            fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("Output file open failed");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        
        if (execvp(args[0], args) < 0) {
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            printf("[Background] Process ID: %d\n", pid);
        }
    }
}

int main() {
    char input[MAX_INPUT];
    signal(SIGINT, handle_signal);

    while (1) {
        display_prompt();
        
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = 0; // Remove newline
        
        execute_command(input);
    }

    printf("\nExiting mini-shell. Goodbye!\n");
    return 0;
}
