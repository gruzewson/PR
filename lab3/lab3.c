#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

    int lvl = 6;

    for (int i = 0; i < lvl; i++) {
        int pid = fork();
        if (pid == 0) {
            if (i == lvl - 1) {
                execlp("ps", "-u root", "-l", "--forest", NULL);
            }
        } else {
            if(i % 2 == 0)
                fork();
            waitpid(pid, NULL, 0);
            break;
        }
    }
    return 0;
}
