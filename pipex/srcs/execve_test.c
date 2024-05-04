#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char *args[] = {"ls", NULL};
    char *envp[] = {NULL};

    printf("%d\n", getpid());
    execve("/usr/bin/ls", args, envp);
    printf("nothing happened");
    perror("execve");
}