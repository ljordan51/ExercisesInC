/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

int globby = 1;
int *pointy = (int*) 5;


// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i)
{
    sleep(i);
    printf("Hello from child %d.\n", i);
    printf("Child %d stack location: %p\n", i, &i);
    printf("Child %d globals location: %p\n", i, &globby);
    printf("Child %d heap location: %p\n", i, &pointy);
    // They are all exactly the same for the globals and heap
    // and the same as the parent. The stack isn't the exact same
    // address but that's because the int isn't passed by reference
    // so it's address is just slightly further down the stack.
    
    // Terminal output:
    // Creating child 0.
    // Creating child 1.
    // Hello from the parent.
    // Parent stack location: 0x7ffc67a8fc2c
    // Parent globals location: 0x55d55801b010
    // Parent heap location: 0x55d55801b018
    // Hello from child 0.
    // Child 0 stack location: 0x7ffc67a8fbfc
    // Child 0 globals location: 0x55d55801b010
    // Child 0 heap location: 0x55d55801b018
    // Child 11457 exited with error code 0.
    // Hello from child 1.
    // Child 1 stack location: 0x7ffc67a8fbfc
    // Child 1 globals location: 0x55d55801b010
    // Child 1 heap location: 0x55d55801b018
    // Child 11458 exited with error code 1.
    // Elapsed time = 1.000601 seconds.
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");
    printf("Parent stack location: %p\n", &i);
    printf("Parent globals location: %p\n", &globby);
    printf("Parent heap location: %p\n", &pointy);

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
