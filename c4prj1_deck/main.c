#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "eval.h"
#include "deck.h"
#include "cards.h"

 

int main(){
  //make full deck
  card_t * fullDeck = malloc(52*sizeof(card_t));
  for ( int i = 0; i < 52; i++){
    fullDeck[i] = card_from_num(i);
  }

  //make hand
  deck_t hand;
  hand.cards = malloc(5*sizeof(card_t *));
  hand.n_cards = 5;
  for ( int i = 0; i < hand.n_cards; i++){
    hand.cards[i] = &fullDeck[i];
    printf("%d: value: %d suit: %d\n", i, hand.cards[i]->value, hand.cards[i]->suit);
  }

  //=== test (1)
  printf("\n ==TEST1==\n");
  card_t c = card_from_num(20);
  add_card_to(&hand, c);
  for ( int i = 0; i < hand.n_cards; i++){
    printf("%d: value %d suit %d\n", i, hand.cards[i]->value, hand.cards[i]->suit); 
  }

  //=== test(2)
  printf("\n ==TEST2==\n");
  //card_t * deck = add_empty_card(&hand);
  //printf("deck: value: %d suit: %d\n", deck->value, deck->suit);

  //=== test(3)
  printf("\n ==TEST3==\n");
  deck_t * newDeck = make_deck_exclude(&hand);
  for ( int i = 0; i < newDeck->n_cards; i++){
    printf("%d: value: %d suit: %d\n", i,  newDeck->cards[i]->value, newDeck->cards[i]->suit);
  }
  
  //frees
  free(fullDeck);
  free(hand.cards[hand.n_cards - 1]);
  free(hand.cards);
  free(*(newDeck->cards));
  free(newDeck->cards);
  return EXIT_SUCCESS;
}
