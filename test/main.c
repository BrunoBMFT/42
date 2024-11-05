#include <signal.h>
#include <stdio.h>

void my_handler(int sig) {
    printf("this is inside the function\n");
}

void	set_sig()
{
	struct sigaction sa;
    
    sa.sa_handler = my_handler;    // Set custom handler
    sigemptyset(&sa.sa_mask);      // Initialize sa_mask to block no signals
    sa.sa_flags = 0;               // No special flags

    sigaction(SIGINT, &sa, NULL);  // Register handler for SIGINT (Ctrl+C)
}

int main()
{
	set_sig();
	while (1)
	{

	}

    return 0;
}