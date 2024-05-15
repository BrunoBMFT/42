#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int i = 0;

int main()
{
    pid_t pid;      // Create a child process using fork()
    printf("here1\n");
    pid = fork();   // makes everything under run twice, since it duplicates the rest of the process
    printf("parent process pid: %d, child's pid: %d.\n", getpid(), pid);
    i++;
    printf("here3\n");
    return 0;
}