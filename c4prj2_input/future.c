#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "future.h"




void add_future_card(future_cards_t *fc, size_t index, card_t * ptr){
  //adds a ptr to the future cards for the given index
  //fc is the deck of future cards, index is the number of the future card, ptr is the pointer to the existing placeholder for that card
  //  (a ptr already added with add_empty_card)
  //if the array does not exist up till that index make the array big enough and fill it with NULL decks
  //fc struct: deck_t * decks, size_t n_decks

  //cases: add ptr to empty fc?? (should be covered by add index much larger or add next index)
  //cases: add ptr to existing index, add ptr to index much larger than existing,  add ptr to next index,
  //===FILL EXISTING INDEX (works)
  if ( index == (fc->n_decks - 1) ){
    if ( fc->decks[index].n_cards > 0 ){
      //add one element to the cards array of the existing index deck_t
      fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards + 1)*sizeof(card_t *));
    }
    //make the last element in this array the input ptr
    fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
    //increment the length of the cards array
    fc->decks[index].n_cards++;
  }
  //===FILL MUCH LARGER INDEX
  else if ( (index > fc->n_decks) ){
    //create null deck 
    deck_t * empty = malloc(sizeof(deck_t));
    empty->cards = malloc(sizeof(card_t *));
    card_t * nullCard = malloc(sizeof(card_t));
    nullCard->value = 0;
    nullCard->suit = NUM_SUITS;
    empty->cards = &nullCard;
    empty->n_cards = 0;

    //fill 0th element first if empty
    if ( fc->n_decks == 0 ) {
      fc->decks[0] = *empty;
      fc->n_decks = 1;
    }
    
    //reallocate fc->decks array to be the size of index + 1
    fc->decks = realloc(fc->decks, (index)*sizeof(deck_t));
    fc->n_decks = index; //the last element should be added later
    
    //find out what indexes need to be filled with null
    // null should be everything from i =  n_decks to i = (index - 1)
    if ( index == fc->n_decks ) {
      goto fillNext;
    }
    //fill empty decks with null
    for ( int i = fc->n_decks; i < index; i++){
      //point the deck element to null and fill in n_cards with 0
      fc->decks[i] = *empty;
    }

    goto fillNext;
  }
  //===FILL NEXT INDEX (works)
  else if ( index == fc->n_decks ){
  fillNext:
    if ( fc->n_decks > 0 ){
      //reallocate fc->decks array to be one element bigger
      fc->decks = realloc(fc->decks, (fc->n_decks + 1)*sizeof(deck_t));
    }
    //build a new deck as usual
    deck_t * new = malloc(sizeof(deck_t));
    new->cards = malloc(sizeof(card_t*));
    //fill the new deck with the ptr to the empty card
    new->cards[0] = ptr;
    new->n_cards = 1;
    //add the new deck to the future decks array
    fc->decks[fc->n_decks] = *new;
    fc->n_decks++;
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
  for (int i = 0; i < fc->n_decks; i++){
    for (int j = 0; j < fc->decks[i].n_cards; j++){
      fc->decks[i].cards[j]->value = deck->cards[i]->value;
      fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
      //deck->cards[i] = fc->decks[i].cards[j];
    }
  }
}
