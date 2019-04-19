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

  for (int i = 0; i < 52; i++){
    print_card(fullDeck[i]);
    printf(" ");
  }
  printf("\n");

  //make hand
  deck_t hand;
  hand.cards = malloc(5*sizeof(card_t *));
  hand.n_cards = 5;
  int index = 0;
  for ( int i = 0; i < hand.n_cards; i++){
    //index = random()%52;
    hand.cards[i] = &fullDeck[i+index];
    print_card(*(hand.cards[i]));
    printf(" ");
    index+=5;
  }
  printf("\n");
  /*
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
  */
  //=== test(3)
  printf("\n ==TEST3==\n");
  deck_t empty;
  empty.cards = NULL;
  empty.n_cards = 0;

  deck_t * newDeck = make_deck_exclude(&empty);
  print_deck(newDeck);

  newDeck->cards = NULL;
  newDeck->n_cards = 0;
  newDeck = make_deck_exclude(&hand);
  print_deck(newDeck);

  //7s 7h 7d 7c 8s 8h 8d 8c 9s 9h 9d 9c 0s 0h
  printf("Build test deck\n");
  card_t test[14];
  test[0] = card_from_letters('7','s');
  test[1] = card_from_letters('7','h');
  test[2] = card_from_letters('7','d');
  test[3] = card_from_letters('7','c');
  test[4] = card_from_letters('8','s');
  test[5] = card_from_letters('8','h');
  test[6] = card_from_letters('8','d');
  test[7] = card_from_letters('8','c');
  test[8] = card_from_letters('9','s');
  test[9] = card_from_letters('9','h');
  test[10] = card_from_letters('9','d');
  test[11] = card_from_letters('9','c');
  test[12] = card_from_letters('0','s');
  test[13] = card_from_letters('0','h');
  deck_t testDeck;
  testDeck.cards = malloc(14*sizeof(card_t*));
  testDeck.n_cards = 14;
  for ( int i = 0; i < testDeck.n_cards; i++){
    //index = random()%52;
    testDeck.cards[i] = &test[i];
    print_card(*(testDeck.cards[i]));
    printf(" ");
  }
  newDeck->cards = NULL;
  newDeck->n_cards = 0;
  newDeck = make_deck_exclude(&testDeck);
  print_deck(newDeck);
  /*
  //=== test(4)
  printf("\n ==TEST4==\n");
  deck_t hand1;
  hand1.cards = malloc(3*sizeof(card_t *));
  hand1.n_cards = 3;
  deck_t hand2;
  hand2.cards = malloc(3*sizeof(card_t *));
  hand2.n_cards = 3;
  deck_t hand3;
  hand3.n_cards = 3;
  hand3.cards = malloc(3*sizeof(card_t *));
  int j = 0;
  for (int i = 0; i < hand1.n_cards; i++){
    hand1.cards[i] = &fullDeck[j];;
    hand2.cards[i] = &fullDeck[j+1];
    hand3.cards[i] = &fullDeck[j+2];
    j+=3;
  }
  deck_t *hands[3] = {&hand1, &hand2, &hand3};
  deck_t *remaining = build_remaining_deck(hands, 3);

  for ( int i = 0; i < remaining->n_cards; i++){
    printf("%d: value: %d suit: %d\n", i, remaining->cards[i]->value, remaining->cards[i]->suit);
  }
  
  //===test (5)
  printf("\n==TEST5 matchCounts==\n");
  
  deck_t Match;
  Match.cards = malloc(6*sizeof(card_t*));
  Match.n_cards = 6;
  Match.cards[0] = &fullDeck[11];
  Match.cards[1] = &fullDeck[24];
  Match.cards[2] = &fullDeck[7];
  Match.cards[3] = &fullDeck[4];
  Match.cards[4] = &fullDeck[17];
  Match.cards[5] = &fullDeck[30];

  unsigned * getMatch = get_match_counts(&Match);

  for (int i = 0; i < Match.n_cards; i++){
    printf("%d: match: %d\n", i, getMatch[i]);
    printf("%d: cardVal: %d\n", i, Match.cards[i]->value);
  }
  */
  //===Frees
  
  //free fullDeck
  free(fullDeck);
  
  //free TEST1
  //free(hand.cards[hand.n_cards - 1]);
  //free hand
  free(hand.cards);
  
  //free TEST3 (make_deck_exclude)
  free(*(newDeck->cards));
  free(newDeck->cards);
  /*
  //free TEST4 (build_remaining_deck)
  free(hand1.cards);
  free(hand2.cards);
  free(hand3.cards);
  //free(*(remaining->cards));
  //free(remaining->cards);
  
  //free TEST5 (get_match_counts)
  free(Match.cards);
  free(getMatch);
  */
  //missing 2 frees
  return EXIT_SUCCESS;
}
