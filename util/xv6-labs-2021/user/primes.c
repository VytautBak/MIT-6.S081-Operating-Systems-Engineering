#include "kernel/types.h"
#include "user/user.h"


int
recurse(int fpipe[]) {
    int prime;


    fprintf(1, "attempting to read my process prime...\n");
    if (read(fpipe[0], &prime, sizeof(int)) == 0) {
        fprintf(1, "exiting bc end\n");
        exit(0);
    }
    
    fprintf(1, "prime %d\n", prime);
    int npipe[2];
    pipe(npipe);
    int buf;
    while (read(fpipe[0], &buf, sizeof(int)) == sizeof(int)) {
        if (buf % prime != 0) {
            write(npipe[1], &buf, sizeof(int));
        }
    }
    close(fpipe[0]);
    close(npipe[1]);
    
    int pid = fork();
    if (pid == 0) {
        fprintf(1, "recursing\n");
        recurse(npipe);
    } else{
        close(npipe[0]);
        wait(0);
    }


    return;
}


int
main(int argc, char* argv[]) {
    int fpipe[2];
    pipe(fpipe);


    int pid = fork();
    if (pid > 0) {
        // parent
        for (int i = 2; i < 36; i++) {
            write(fpipe[1], &i, sizeof(int));
        }
        close(fpipe[1]);
        wait(pid);
    } else {
        fprintf(1, "started firsts child");
        recurse(fpipe);
    }

}