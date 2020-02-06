/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}

/*
1. It seems like it should print the number 42 5 times.
    But since array is a local var in foo() it will go
    away once foo() is done executing and *array in main
    will point to something that no longer exists.
2. Ya basically letting us know that you shouldn't return the address of a
    local variable since it won't exist after the return happens.
stack.c: In function ‘foo’:
stack.c:22:12: warning: function returns address of local variable [-Wreturn-local-addr]
     return array;
            ^~~~~
3. Sort of redundant to describe what's happening at this point but I got a
    Segmentation fault (core dumped) after both foo() and bar() ran so likely when the for
    loop trys to access array.
4. The prints no longer happen. Just confirms that both foo() and bar()
    are executed before the Segmentation fault (core dumped).
*/