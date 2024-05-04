#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = 9; 
    printf("main process (before fork), pid: %d.\n", getpid());
    // Create a child process using fork()
    pid = fork();
    printf("------------------------------------\n");     
    printf("main process (after fork), pid: %d.\n", getpid());
    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork2 failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("child process, pid: %d, child's pid: %d\n", getpid(), pid);
    } else {
        // Parent process
        printf("parent process, pid: %d, child's pid: %d.\n", getpid(), pid);
    }

    return 0;
}