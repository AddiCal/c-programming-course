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

  //set up deck
  deck_t *  ans = malloc(sizeof(deck_t));
  ans->cards = malloc(sizeof(card_t*));
  ans->n_cards = 0;

  //set up cards array
  card_t ** cards = malloc(sizeof(card_t*));
    
  //copy const string to something we can play with
  char temp[strlen(str)+1];
  strcpy(temp, str);

  //track place in file
  const char * ptr = str;
  int i = 0;
  
  //get cards by splitting on spaces
  char * strCard = strtok(temp, " ");

  while ( *ptr != '\n'){
    //97 is DEC for ascii letter 'a' (ie. skip spaces and lower case letters and the number that comes after a '?')
    if ( (*ptr == ' ') || (*ptr > 96) ){ // || (lastCard[0] == '?' ) ){
      ptr++;
      continue;
    }
    
    //get new card if i > 0
    if ( i > 0 ){
      strCard = strtok(NULL, " ");
    }

    //deal with future cards
    if ( strCard[0] == '?' ){
      if ((strCard[1] < 48) || (strCard[1] > 57)){ //checks to make sure ? is followed by a digit
	fprintf(stderr, "ERROR: invalid format for future card in input file\n");
	exit(EXIT_FAILURE);
      }
      //add empty card //fill in with future card with index 
      char * rest = strCard;
      char * temp = strtok_r(rest, "?", &rest);
      int index = atoi(temp);
      //add empty card and increment n_cards
      card_t * spot = add_empty_card(ans);
      add_future_card(fc, index, spot);

      int len = strlen(temp);
      int count = 0;
      for ( int i = 0; i < len; i++ ){
	if ( temp[i] == '\n' ){
	  count++;
	}
      }
      ptr+=(len+1-count);
      i++;
      continue;
    }

    //add regular card to hand
    else {
      if ( i > 0 ){
	ans->cards = realloc(ans->cards, (i+1)*sizeof(card_t*));
	cards = realloc(cards, (i+1)*sizeof(card_t*));
      }
      cards[i] = malloc(sizeof(card_t));
      *cards[i] = card_from_letters(strCard[0], strCard[1]);

      ans->cards[i] = cards[i];
      ans->n_cards++;
    }
    i++;
    ptr++;
  }
  //return error if hand has less than 5 cards
  if ( ans->n_cards < 5 ){
    fprintf(stderr, "ERROR: hand must be at least 5 cards\n");
    exit(EXIT_FAILURE);
  }
  
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
  char * line = NULL;
  int i = 0;
  //fill in first element
  //printf("hands from input file:\n");
  while ( getline(&line, &size, f) >= 0){
    //parse line in to hands
    if ( strcmp(line, "\n") == 0 ){
      continue;
    }
    
    if ( i > 0 ) {
      ans = realloc(ans, (i+1)*sizeof(deck_t*));
    }

    //is this step necessary?
    ans[i] = malloc(sizeof(deck_t*));
    
    ans[i] = hand_from_string(line, fc);
    line = NULL;
    i++;
  }
  //==free all the decks once i've use them!!==
  *n_hands = i;
  free(line);

  return ans;
}
