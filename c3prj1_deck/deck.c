#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
  //use printcard fxn i've already written
  //deck_t has card_t **cards and size_t n_cards
  //card_t has 2<=value<=14 and 0<=suit<=4
  for (int i = 0; i < (hand->n_cards); i++){
    print_card(*(hand->cards[i])); //dereference cards?
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  //search a deck for a particular card
  //deck_t has card_t **cards and size_t n_cards
  //card_t has 2<=value<=14 and 0<=suit<=4
  for (int i = 0; i < (d->n_cards); i++){
    if (( (d->cards[i]->value) == c.value) && ( (d->cards[i]->suit) == c.suit)){//is this how you index an array of structs?
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  //random swapping
  //swap i with random j in the deck for each i
  card_t swap;
  int swapIndex;
  for (int i = 0; i < (d->n_cards); i++){//does this need double indexing?
    swap = *(d->cards[i]);
    swapIndex = random()%(d->n_cards);//generates a random number from 0 to #cards in deck
    *(d->cards[i]) = *(d->cards[swapIndex]);
    *(d->cards[swapIndex]) = swap;
  } 
}

void assert_full_deck(deck_t * d) {
  //check that each card only appears once per deck
  
  //check that the lengths of the decks are the same length
  assert((d->n_cards) = 52);

  //use deck contains and card_from_num fxn to check how many times a card appears in the deck
  int count;
  card_t temp;
  for (int i = 0; i < 52; i++){ //scroll through list of possible cards
    for (int j = 0; j < (d->n_cards); j++){ //scroll through input deck
      temp = card_from_num(i);
      if ( ( (d->cards[j]->value) == temp.value) && ( (d->cards[j]->suit) == temp.suit)){
	count++;
      }
    }
    //if card occurs more than once return error
    if (count > 1){
      printf("ERROR: deck has repeating card ");
      print_card(temp);
      printf("\n");
      return;
    }
    else{
      count = 0;
    }
  }  
}
