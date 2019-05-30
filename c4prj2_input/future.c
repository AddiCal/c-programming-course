#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "future.h"


void printDECK(deck_t * deck){
  printf("\n");
  for ( int i = 0; i < deck->n_cards; i++){
    if ( deck->cards[i]->suit == NUM_SUITS ){
      printf("?? ");
      continue;
    }
    print_card(*(deck->cards[i]));
    printf(" ");
  }
  printf("\n");
}

void printFC(future_cards_t * fc){
  printf("fc->n_decks: %zu\n", fc->n_decks); 
  for (int i = 0; i < fc->n_decks; i++){
    printf("index: %d", i);
    printDECK(&(fc->decks[i]));
  }
}



void add_future_card(future_cards_t *fc, size_t index, card_t * ptr){
  //adds a ptr to the future cards for the given index
  //fc is the deck of future cards, index is the number of the future card, ptr is the pointer to the existing placeholder for that card
  //  (a ptr already added with add_empty_card)
  //if the array does not exist up till that index make the array big enough and fill it with NULLdecks
  //fc struct: deck_t * decks, size_t n_decks
  if ( !(fc->n_decks) | (fc->n_decks==0)){
    fc->n_decks = 0;
  }
  if (!(fc->decks)){
    //add empty deck
  }
  if ( (index < fc->n_decks) ){
    //===CASE0: FILL EMPTY FC===
    //if deck is empty you also have to create a new deck and replace the old one
    //if existing deck is empty, create a new deck and replace the old one
    if ( fc->decks[index].n_cards == 0 ) {
      deck_t * newDeck = malloc(sizeof(deck_t));
      newDeck->cards = malloc(sizeof(card_t*));

      card_t ** newCards = malloc(sizeof(card_t*));
      newCards[0] = malloc(sizeof(card_t));
      newCards[0] = ptr;

      newDeck->cards[0] = newCards[0];
      newDeck->n_cards = 1;

      fc->decks[index] = newDeck[0];
      fc->decks[index].n_cards = 1;
    }
    //===CASE2: FILL EXISTING INDEX===
    //if existing deck is not empty, update it the way you'd think
    else {
      //make cards array larger and add card
      //printf("index: %zu, n_decks: %zu, n_cards: %zu\n", index, fc->n_decks, fc->decks[index].n_cards);
      card_t ** newCards = malloc(sizeof(card_t*));
      newCards[0] = malloc(sizeof(card_t));
      newCards[0] = ptr;

      if ( fc->decks[index].n_cards > 0 ){
	fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards + 1)*sizeof(card_t*));
      }

      fc->decks[index].cards[fc->decks[index].n_cards] = newCards[0];
      fc->decks[index].n_cards++;
    }  
  }
  //===CASE1: FILL LARGER INDEX===
  else if ( (index >= fc->n_decks) ) {

    card_t ** newCards = malloc(sizeof(card_t*));
    newCards[0] = malloc(sizeof(card_t));

    card_t emptycard;
    emptycard.value = 0;
    emptycard.suit = NUM_SUITS;

    *newCards[0] = emptycard;

    
    deck_t * empty = malloc(sizeof(deck_t));
    empty->cards = malloc(sizeof(card_t*));
    empty->cards[0] = newCards[0];
    empty->n_cards = 0;
    

    //fill in 0th element if fc is empty
    if ( fc->n_decks == 0 ){
      fc->decks = malloc((1)*sizeof(deck_t));
      fc->decks[0] = empty[0];
      fc->n_decks = 0;
    }
      
    if ( index > 0 ) {
      //reallocated fc decks array to be index+1 elements larger
      fc->decks = realloc(fc->decks, (index+1)*sizeof(deck_t));
      
      //fill in fc with empty decks except for index
      for ( int i = fc->n_decks; i < index; i++) {
	fc->decks[i] = empty[0];
      }
    }
      
    //fill in fc at index with input ptr
    deck_t * newDeck = malloc(sizeof(deck_t));
    newDeck->cards = malloc(sizeof(card_t*));
    
    newCards = realloc(newCards, 2*sizeof(card_t*));
    newCards[1] = malloc(sizeof(card_t));
    newCards[1] = ptr;
    
    
    newDeck->cards[0] = newCards[1];
    newDeck->n_cards = 1;

    //=====\/this is where my invalid write comes from=====
    fc->decks[index] = newDeck[0];
    fc->n_decks = index+1;
  } 
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  //takes a shuffled deck and a filled fc and assignes values to the future cards from the deck in order
  //  so index 0 of the deck corresponds to ?0 in future cards
  //point the pointers in fc to the cards in deck??
  //print error message??
  
  if( deck->n_cards < fc->n_decks){
    printf("ERROR: not enough cards in deck to fill future cards\n");
    exit(EXIT_FAILURE);
  }
  int k = 0;
  for (int i = 0; i < fc->n_decks; i++){
    if (fc->decks[i].n_cards == 0){
      continue;
    }
    for (int j = 0; j < fc->decks[i].n_cards; j++){
      //printf("deck: %d, card: %d\n", i, j);
      fc->decks[i].cards[j]->value = deck->cards[i]->value;
      fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
      //fc->decks[i].cards[j] = deck->cards[k];
    }
    k++;
  }
  //===REMOVE BEFORE COMMITTING===
  //printFC(fc);
  //printf("\n");
  //===
  
  //remove all non-empty decks from FC so that the cards don't get double freed
  int count = 0;
  //loop through all decks in fc
  for ( int i = 0; i < fc->n_decks; i++){
    //if the deck isn't empty, remove that element by shifting the array elements back one (you'll have empty crap at the end)
    if ( fc->decks[i].cards[0]->suit != NUM_SUITS){
      for (int k = i; k < (fc->n_decks - 1); k++){
	fc->decks[i] = fc->decks[i+1];
      }
      if (fc->decks[i].cards[0]->suit != NUM_SUITS){
	i-=1;
      }
      fc->n_decks--;
      count++;
    }
  }//end loop through decks in fc

  if ( count > 0 ){
    fc->decks = realloc(fc->decks, (fc->n_decks)*sizeof(deck_t));
  }
  
}
