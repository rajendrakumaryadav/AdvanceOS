#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
void handle_signal_int(int sig)
{
    printf("Signal Received, But ignored!");
} // Ctrl + c - SIGINT | Ctrl + \ - SIGQUIT

int main() {
    signal(SIGINT, handle_signal_int);
    signal(SIGQUIT, handle_signal_int);

    while(1) {
        raise(SIGINT);
        sleep(1);
    }
    return 0;
}