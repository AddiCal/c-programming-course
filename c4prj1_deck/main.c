#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "eval.h"
#include "deck.h"
#include "cards.h"

void print_deck(deck_t * deck){
  printf("\n");
  for ( int i = 0; i < deck->n_cards; i++){
    print_card(*(deck->cards[i]));
    printf(" ");
  }
  printf("\n");
} 

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
  int index = 0;
  for ( int i = 0; i < hand.n_cards; i++){
    hand.cards[i] = &fullDeck[i+index];
    print_card(*(hand.cards[i]));
    printf(" ");
    index+=5;
  }
  printf("\n");

  //===TEST1
  printf("===TEST1===\n");
  deck_t * TEST1 = make_deck_exclude(&hand);
  print_deck(TEST1);

  free_deck(TEST1);

  //===TEST2
  printf("===TEST2===\n");
  deck_t hand2;
  index = 3;
  for ( int i = 0; i < hand.n_cards; i++){
    hand2.cards[i] = &fullDeck[i+index];
    print_card(*(hand.cards[i]));
    printf(" ");
    index+=5;
  }
  printf("\n");

  deck_t hand3;
  index = 4;
  for ( int i = 0; i < hand.n_cards; i++){
    hand3.cards[i] = &fullDeck[i+index];
    print_card(*(hand.cards[i]));
    printf(" ");
    index+=5;
  }
  printf("\n");

  deck_t *hands[3] = {&hand, &hand2, &hand3};

  deck_t * TEST2 = build_remaining_deck(hands, 3);
  print_deck(TEST2);
  //===Frees
  free(fullDeck);
  free(hand.cards);
  return EXIT_SUCCESS;
}
