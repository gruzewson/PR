#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1
#define INPUT_BUFFER_SIZE 128
#define CONTINUE 1
#define EXIT 0

void transformation_letters(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

void transformation_numbers(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            str[i] = '.';
        }
    }
}

void input(int pipe1[2], int pipe2[2], int pid) {
    close(pipe1[READ]);
    close(pipe2[WRITE]);
    int status = CONTINUE;
    char message[INPUT_BUFFER_SIZE];
    printf("INPUT: enter a message: (q if you want to exit)\n");
    scanf("%s", message);
    if (strcmp(message, "q") == 0) {
        status = EXIT;
    }

    write(pipe1[WRITE], &status, sizeof(status));

    if (status == EXIT) {
        printf("INPUT: quits.\n");
        close(pipe1[WRITE]);
        waitpid(pid, NULL, 0);
        exit(0);
    }
    write(pipe1[WRITE], message, sizeof(message));
    sleep(5);
}

void transform1(int pipe1[2], int pipe2[2], int pid) {
int status;
    read(pipe1[READ], &status, sizeof(status));
    close(pipe1[WRITE]);
    close(pipe2[READ]);
    if(status == EXIT) {
        write(pipe2[WRITE], &status, sizeof(status));
        close(pipe1[READ]);
        close(pipe2[WRITE]);
        waitpid(pid, NULL, 0);
        exit(0);
    }
    
    char message[INPUT_BUFFER_SIZE];
    read(pipe1[READ], &message, sizeof(message));
    char old_message[INPUT_BUFFER_SIZE];
    strcpy(old_message, message);
    transformation_letters(message);

    printf("TRANSFORM: transforms '%s' to '%s'.\n", old_message, message);
    write(pipe2[WRITE], &status, sizeof(status));

    write(pipe2[WRITE], &message, sizeof(message));
}

void transform2(int pipe1[2], int pipe2[2]) {
    int mypipe;
    mypipe = open("mypipe", O_WRONLY);
    close(pipe1[READ]);
    close(pipe2[WRITE]);
    close(pipe2[WRITE]);
    int status;
    read(pipe2[READ], &status, sizeof(status));
    if(status == EXIT) {
        write(mypipe, &status, sizeof(status));
        close(pipe1[READ]);
        close(pipe2[WRITE]);
        close(mypipe);
        exit(0);
    }
    char message[INPUT_BUFFER_SIZE];
    char old_message[INPUT_BUFFER_SIZE];
    read(pipe2[READ], &message, sizeof(message));
    strcpy(old_message, message);
    transformation_numbers(message);

    printf("TRANSFORM2: transforms '%s' to '%s'.\n", old_message, message);
    write(mypipe, &status, sizeof(status));

    write(mypipe, &message, sizeof(message));
}

int main() {
  
    while (1) {
        int pipe1[2];
        pipe(pipe1);
        int pipe2[2];
        pipe(pipe2);

        int pid = fork();
        if (pid == -1) {
            perror("fork() failed");
            exit(1);
        }

        if (pid != 0) {
            input(pipe1, pipe2, pid);
        } else {
            int pid2 = fork();
            if (pid2 == -1) {
            perror("fork() failed");
            exit(1);
            }

            if (pid2 != 0) {
                transform1(pipe1, pipe2, pid2);
            } else {
                transform2(pipe1, pipe2);
            }
        }
    }
    return 0;
}