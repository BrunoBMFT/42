#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void    callexecve()
{
    char *const args[] = { "ls", NULL };
    char *const envp[] = { NULL };

    execve("/usr/bin/ls", args, envp);
    perror("execve");
    exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}
int main(void)
{
    pid_t pid;

    pid = 9; 
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork2 failed.\n");
        return 1;
    }
    else if (pid == 0)//here usually separate so i can visualize better during testing (1 function for parent and 1 for child)
    {
        printf("child, also parent\n");
        callexecve();
    }
    else if (pid > 1)
    {
        printf("parent\n");
        waitpid(pid, NULL, 0); 
        printf("back to parent\n");
    }
}