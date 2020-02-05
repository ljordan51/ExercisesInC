/*
  This program implements a simple card counting algorithm.
  Author: Lucky Jordan
  Date: 2/5/2020
  Class: Software Systems Spring 2020
*/

#include <stdio.h>
#include <stdlib.h>

/* Prompts the user for input and puts the reply in the given buffer.

   User input is truncated to the first two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/
void get_card_name(char *prompt, char *card_name) {
  puts(prompt);
  scanf("%2s", card_name);
}

/* Returns the value of a card based on the card name.

   If the card value isn't known, msg is displayed and the return value
   is -1.

   msg: string message to display when card value isn't known
   card_name: the name of the card as a char array
   
   return: int value of card, returns -1 if card name isn't recognized
*/
int get_card_value(char *msg, char *card_name) {
  int val = -1;
  switch(card_name[0]) {
    case 'K':
    case 'Q':
    case 'J':
      val = 10;
      break;
    case 'A':
      val = 11;
      break;
    case 'X':
      val = -1;
      break;
    default:
      val = atoi(card_name);
      if ((val<2) || (val>10)) {
        puts(msg);
        val = -1;
      }
  }
  return val;
}

/* Calculates, prints and updates the count.

   msg: string message to display before the count
   val: the value of the card
   count: int where count is stored
*/
void print_new_count(char *msg, int val, int *count) {  
  if ((val > 2) && (val < 7)) {
    *count = *count + 1;
  } else if (val == 10) {
    *count = *count - 1;
  }
  printf(msg, *count);
}

int main()
{
  char card_name[3];
  int count = 0;
  int val = 0;
  while ( card_name[0] != 'X' ) {
    get_card_name("Enter the card_name: ", card_name);
    val = get_card_value("I don't understand that value!", card_name);
    if (val != -1) {
      print_new_count("Current count: %i\n", val, &count);
    }
  }
  return 0;
}