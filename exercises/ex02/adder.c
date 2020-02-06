/*
This program allows the user to enter integers, one per line, until the user
hits Control-D. After the user enters Control-D, the program adds up the
numbers and prints the result.

This program throws an error if the user enters something that can't be
converted to an integer. This program also throws an error if the user enters
an integer that has more than 6 digits.

Note: I got pretty frustrated trying to make the program not accept input
"that exceeds the length of the input buffer" because if the buffer is
exceeded then the rest justs sits in stdin and automatically gets read on the
next cycle. I really could not find a way to prevent this from happening
and after looking at other solutions from past years I couldn't
immediately find anyone who actually handled this the way it is described in
the assignment so I decided to do something more along the lines of what others
did: set a large buffer size and a separate maximum integer length.

Author: Lucky Jordan
Date: 2/6/2020
Class: Software Systems Spring 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_INTEGERS      5
#define MAX_DIGITS_PER_INT    6
#define BUFFER_SIZE           20

/*
This function gets user input of integers and stores them in an int array.
User input terminates either by pressing ctrl+d or when the number of integers
entered equals the MAX_NUM_INTEGERS. It limits the number of digits of any
integer to MAX_DIGITS_PER_INT.

Issues:
  If the entry length exceeds BUFFER_SIZE the program is unpredictable.
  If the user enters a non-integer which exceeds the MAX_DIGITS_PER_INT length
    they may be confused by the error message prompting them to enter an
    integer below 1,000,000 when really they should first be told that their
    entry cannot be converted to an integer.

integers: int array in which to store numbers
*/
int get_integers(int *integers) {
  char input[BUFFER_SIZE];
  int val;
  int num_entered = 0;
  while(num_entered<MAX_NUM_INTEGERS){
    // need to check if input exceeded length of buffer
    if (fgets(input, BUFFER_SIZE, stdin) == NULL){
      break;
    }
    if (strlen(input)>MAX_DIGITS_PER_INT+1){
      puts("That entry was too long. Try entering an integer below 1,000,000.");
      continue;
    }
    val = atoi(input);
    if (val==0 && strcmp(input,"0")!=0){
      puts("Can't be converted to an integer. Try again!");
      continue;
    }
    integers[num_entered] = atoi(input);
    num_entered++;
  }
  return num_entered;
}

/*
This function calculates and prints the sum of the first n elements of an array
of integers.

integers: int array of numbers to sum
n: number of elements to sum
*/
void calc_and_print_sum(int *integers, int n) {
  int sum = 0;
  for (int j=0;j<n;j++){
    sum+=integers[j];
  }
  printf("Sum: %i\n", sum);
  
}

int main() {
  int integers[MAX_NUM_INTEGERS];
  int num_entered;
  puts("Yo yo yo enter dem ints. Please enter one integer per line.");
  printf(
    "You can enter up to %i integers. Pres ctrl+d to quit.\n",
    MAX_NUM_INTEGERS);
  num_entered = get_integers(integers);
  calc_and_print_sum(integers, num_entered);
  return 0;
}