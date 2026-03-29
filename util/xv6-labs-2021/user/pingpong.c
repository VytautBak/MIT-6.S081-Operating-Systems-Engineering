#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char* argv[]) {
    
    int mc[2];
    int cm[2];

    // main to child
    pipe(mc);

    // child to main
    pipe(cm);

    int pid = fork();
    if (pid == 0) {
        // child
        char cbyte;
        read(mc[0], &cbyte, 1);
        int child_pid = getpid();
        fprintf(1, "%d: received ping\n", child_pid);
        write(cm[1], cbyte, 1);
        exit(0);
    } else {
        // parent
        write(mc[1], "a", 1);
        char pbyte;
        read(cm[0], &pbyte, 1);
        int parent_pid = getpid();
        fprintf(1, "%d: received pong\n", parent_pid);
        exit(0);
    }
}