#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = 9; 
    printf("main (before), pid: %d.\n", getpid());
    // Create a child process using fork()
    pid = fork();//as soon as fork happens, the value of pid changes to +=1
    printf("\n------------------------------------\n");     
    printf("main (after), pid: %d.\n", getpid());
    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork2 failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("child, pid: %d, child's pid: %d\n", getpid(), pid);
    } else {
        // Parent process
        printf("parent, pid: %d, child's pid: %d.\n", getpid(), pid);
    }

    return 0;
}