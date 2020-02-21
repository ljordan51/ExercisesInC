/*
UNIX tee command implementation

Author: Lucky Jordan
Class: Software Systems Spring 2020
Date: 2/20/20
*/

/*
Q1: This chapter in Head First C was very helpful. Copying from there and
making small changes was very hepful. Trying to grab multiline complicated
stuff from the internet was often challenging since I didn't understand how
each part worked.
Q2: They use malloc and free. They also have error messages. The code is
broken into many blocks with some static declarations. It looks like it gives
the ability to see instructions from the usage function as well.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

int main (int argc, char* argv[]){
  char ch;
  int append = 0;
  char in[512];
  FILE *output_file;
  int i = 0;

  while((ch = getopt(argc, argv, "a")) != EOF){
    switch(ch){
      case 'a':
        append = 1;
        break;
      default:
        fprintf(stderr, "Unknown option: '%s'\n", optarg);
        return 1;
    }
  }

  argc -= optind;
  argv += optind;


  while(fgets(in, 512, stdin)){
   for(i=0; i<argc; i++){
     if(!append){
       output_file = fopen(argv[i], "w");
       append = 1;
     }
     else{
       output_file = fopen(argv[i], "a");
     }

     fputs(in, output_file);

     fclose(output_file);
   }
 }

return 0;
}