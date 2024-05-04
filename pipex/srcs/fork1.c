#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;    // Create a child process using fork()
    pid = fork();
   printf("parent process pid: %d, child's pid: %d.\n", getpid(), pid);
   return 0;
}