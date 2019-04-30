#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "future.h"
#include "eval.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  //allocate a deck_t for this hand, hand must have at least 5 cards
  //read in the line, separate by space delimiter, use card_from_letter
  //future cards need to be filled in with an empty card
  //use add_card_to, card_from_letter, and future fxns to write this

  deck_t * ans = malloc(sizeof(deck_t*));
  ans->cards = malloc(sizeof(card_t*));

  //copy const string to something we can play with
  char temp[strlen(str)+1];
  strcpy(temp, str);

  const char * ptr = str;
  int i = 0;
  while ( *ptr != '\n'){
    //get cards by splitting on spaces
    const char * strCard = strtok(temp, " ");

    //deal with future cards
    if (strstr(strCard, "?") == 0){
      //add empty card //fill in with future card with index strCard[1] (convert to int)
      char temp[2];
      temp[0] = strCard[1];
      temp[1] = '\0';
      int index = atoi(temp);
      card_t * spot = add_empty_card(ans);
      add_future_card(fc, index, spot);
    }
    //add regular card to hand
    else {
      card_t * card = malloc(sizeof(card_t));
      *card = card_from_letters(strCard[0], strCard[1]);
      ans->cards[i] = card;
    }
    i++;
    ptr++;
  }
  
  ans->n_cards = i;
  return ans;
}


deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  //reads the hands from the input file, one hand per line, cards separated by space
  //a hand must have at least 5 cards or else it's an error
  //alloc a deck_t for each hand and place it in to an allocated array of pointers
  //return the number of lines we read to n_hands the same way get_line returns the string it read
  //future cards in the hands (?0, ?1, ?7, ..) need to be filled in with and empty card and then add future card
  //add_card_to and card_from_letters will be helpful
  //also, write a fxn to parse a single hand from a single get_line

  //0. set up structs (array of pointers to decks)
  deck_t ** ans = malloc(sizeof(deck_t*));
  
  //1. getline setup
  size_t size = 0;
  size_t len = 0;
  char * line = NULL;
  int i = 0;
  while ( (len = getline(&line, &size, f)) >= 0){
    //parse line in to hands
    ans[i] = hand_from_string(line, fc);
    i++;
  }
  *n_hands = i;
  free(line);

  return ans;
}