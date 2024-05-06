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

void    child()
{
    printf("child, also parent\n");
    callexecve();
}

void    parent()
{
    wait(NULL); 
    printf("back to parent\n");
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
    else if (pid == 0)
        child();//runs second
    else if (pid > 1)//runs first
    {
        printf("parent\n");
        waitpid(pid, NULL, 0);//waits till second is done
        parent();//runs third
    }
}