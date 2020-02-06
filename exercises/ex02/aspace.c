/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

Edited by: Lucky Jordan
Date: 2/6/2020
Class: Software Systems Spring 2020

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void print_local(){
  char local;
  printf("Address of local is %p\n", &local);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    void *k = malloc(128);
    char *s = "Hello, World";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("s points to %p\n", s);
    printf ("k points to %p\n", k);
    
    print_local();

    return 0;
}

/*
3.  Stack | var2 0x7ffce128e324
          |_______________
    Heap  | *p   0x55a9d33a3260
          |_______________
  Globals | var1 0x55a9d3152014
          |_______________
Constants | *s   0x55a9d2f51854
          | main 0x55a9d2f516fa // not sure about this
          |_______________
    Code  |
          |_______________

4.  Stack | var2 0x7ffe02862e5c
          |_______________
    Heap  | *k   0x55ffe85122f0 // address grew up
          | *p   0x55ffe8512260 // space between addresses is 128
          |_______________
  Globals | var1 0x55ffe789e014
          |_______________
Constants | *s   0x55ffe769d874
          | main 0x55ffe769d6fa // not sure about this,but the space between
          |                     // *s and main grew which makes me think they
          |                     //  are in the same section
          |_______________
    Code  |
          |_______________
          
5.  Stack | var2 0x7ffe7632e7ec
          |local 0x7ffe7632e7c7 // address grew down
          |_______________
    Heap  | *k   0x562cb80982f0
          | *p   0x562cb8098260
          |_______________
  Globals | var1 0x562cb70bc014
          |_______________
Constants | *s   0x562cb6ebb8dc
          | main 0x562cb6ebb740 // space grew a bit more
          |_______________
    Code  |
          |_______________
          
6. Already did this basically when checking space between *k and *p.
    Don't feel the need to check again.
*/