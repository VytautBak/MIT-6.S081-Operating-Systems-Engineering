#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(2, "Usage: sleep n, e.g. sleep 5 sleeps for 5 ticks\n");
        exit(1);
    }
    fprintf(1, "Sleeping for %s ticks\n", argv[1]);
    sleep(atoi(argv[1]));
    exit(0);
}