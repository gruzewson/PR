#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define INPUT_BUFFER_SIZE 128
#define WORK 1
#define EXIT 0

void transformation(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        } else if (str[i] >= '0' && str[i] <= '9') {
            str[i] = '.';
        }
    }
}

void input(int pipe1[2], int pipe2[2], int pid, int* status) {
    close(pipe1[READ]);
    close(pipe2[WRITE]);
    char message[INPUT_BUFFER_SIZE];
    printf("INPUT: enter a message: (q if you want to exit)\n");
    scanf("%s", message);

    if (strcmp(message, "q") == 0) {
        *status = EXIT;
        printf("INPUT: quits.\n");
        close(pipe1[WRITE]);
        close(pipe2[READ]);
        return;
    }
    write(pipe1[WRITE], message, sizeof(message));
}

void transform(int pipe1[2], int pipe2[2], int pid) {
    close(pipe1[WRITE]);
    close(pipe2[READ]);

    char message[INPUT_BUFFER_SIZE];
    char old_message[INPUT_BUFFER_SIZE];
    read(pipe1[READ], message, sizeof(message));
    strcpy(old_message, message);
    transformation(message);
    printf("TRANSFORM: transforms '%s' to '%s'.\n", old_message, message);

    write(pipe2[WRITE], message, sizeof(message));
}

void display(int pipe1[2], int pipe2[2]) {
    close(pipe1[READ]);
    close(pipe1[WRITE]);
    close(pipe2[WRITE]);
    char message[INPUT_BUFFER_SIZE];
    read(pipe2[READ], message, sizeof(message));

    printf("DISPLAY: has read '%s'.\n", message);
}

int main() {
    while (1) {
        int pipe1[2];
        pipe(pipe1);
        int pipe2[2];
        pipe(pipe2);
        int status = WORK;

        int pid = fork();
        if (pid == -1) {
            perror("fork() failed");
            exit(1);
        }

        if (pid != 0) {
            input(pipe1, pipe2, pid, &status);
            if (status == EXIT) {
                break;
            }
            wait(NULL);
        } else{
            int pid2 = fork();
            if (pid2 == -1) {
                perror("fork() failed");
                exit(1);
            }

            if (pid2 != 0) {
                transform(pipe1, pipe2, pid2);
                exit(0);
            } else {
                display(pipe1, pipe2);
                exit(0);
            }
        }
    }
    return 0;
}
