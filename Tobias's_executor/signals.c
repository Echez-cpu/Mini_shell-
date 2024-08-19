#include <stdio.h>
#include <signal.h>

int main (void);

void handle_sigint(int sig) 
{ 
    printf("Caught signal %d\n", sig); 
    sigact();
} 

int main (void)
{
    signal(SIGINT, handle_sigint); 
    printf("starting...\n");
    while(1)
    ;
    return 0;
}