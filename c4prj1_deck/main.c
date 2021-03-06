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
  card_t ** fullDeck = malloc(52*sizeof(card_t*));
  for ( int i = 0; i < 52; i++){
    //fullDeck = realloc(fullDeck, (i+1)*sizeof(card_t));
    fullDeck[i] = malloc(sizeof(card_t));
    *fullDeck[i] = card_from_num(i);
  }

  //make hand
  deck_t *hand = malloc(sizeof(deck_t));
  hand->cards = malloc(5*sizeof(card_t *));
  //hand->cards = NULL;
  hand->n_cards = 5;
  int index = 0;
  for ( int i = 0; i < hand->n_cards; i++){
    //hand->cards = realloc(hand->cards, (i+1)*sizeof(card_t*));
    hand->cards[i] = fullDeck[i+index];
    print_card(*(hand->cards[i]));
    printf(" ");
    index+=5;
  }
  printf("\n");
  //hand->n_cards = 5;
  /*
  //===TEST1
  printf("===TEST1===\n");
  deck_t * TEST1 = make_deck_exclude(hand);
  print_deck(TEST1);
  //free(*(TEST1->cards));
  free_deck(TEST1);
  */
  //===TEST2
  printf("===TEST2===\n");
  deck_t * hand2 = malloc(sizeof(deck_t));
  hand2->cards = malloc(5*sizeof(card_t *));
  hand2->n_cards = 5; 
  index = 3;
  for ( int i = 0; i < hand->n_cards; i++){
    hand2->cards[i] = fullDeck[i+index];
    print_card(*(hand2->cards[i]));
    printf(" ");
    index+=3;
  }
  printf("\n");

  deck_t * hand3 = malloc(sizeof(deck_t));
  hand3->cards = malloc(5*sizeof(card_t *));
  hand3->n_cards = 5;
  index = 4;
  for ( int i = 0; i < hand->n_cards; i++){
    hand3->cards[i] = fullDeck[i+index];
    print_card(*(hand3->cards[i]));
    printf(" ");
    index+=5;
  }
  printf("\n");

  deck_t **hands = malloc(3*sizeof(deck_t*));
  hands[0] = hand;
  hands[1] = hand2;
  hands[2] = hand3;

  for (int i = 0; i < 3; i++){
    print_deck(hands[i]);
  }

  deck_t * TEST2 = build_remaining_deck(hands, 3);
  print_deck(TEST2);

  free_deck(hand2);
  free_deck(hand3);
  free(hands);
  //free(*(TEST2->cards));
  free_deck(TEST2);
  
  //===Frees
  for ( int i = 0; i < 52; i++){
    free(fullDeck[i]);
  }
  free(fullDeck);
  free_deck(hand);
  return EXIT_SUCCESS;
}
