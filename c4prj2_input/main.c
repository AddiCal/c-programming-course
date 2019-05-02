#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "eval.h"
#include "deck.h"
#include "cards.h"
#include "future.h"
#include "input.h"

void print_deck(deck_t * deck){
  printf("\n");
  for ( int i = 0; i < deck->n_cards; i++){
    print_card(*(deck->cards[i]));
    printf(" ");
  }
  printf("\n");
} 

int main( int argc, char ** argv){
  //built test deck and add empty cards
  card_t ** cards = malloc(52*sizeof(card_t*));
  int len = 5;
  deck_t * ans = malloc(sizeof(deck_t));
  ans->cards = malloc(len*sizeof(card_t*));

  deck_t * test2 = malloc(sizeof(deck_t));
  test2->cards = malloc(len*sizeof(card_t*));
  
  int k = 0;
  for ( int i = 0; i < 13; i++ ){
    for ( int j = 0; j < 4; j++ ){
      cards[k] = malloc(sizeof(card_t));
      *cards[k] = card_from_num(i+13*j);
      k++;
    }
  }

  for ( int i = 0; i < 5; i++){
    ans->cards[i] = cards[(i+3)*(5)];
    test2->cards[i] = cards[(i+4)*6];
  }
  ans->n_cards = len;
  test2->n_cards = len;
  
  printf("ans: \n");
  print_deck(ans);
  printf("test2: \n");
  print_deck(test2);
  
  //===TEST1===

  printf("===TEST1===\n");

  //get ptr to empty card
  card_t * spot1 = add_empty_card(ans);
  card_t * spot2 = add_empty_card(ans);
  card_t * spot3 = add_empty_card(ans);

  //create future card struct
  future_cards_t * fc = malloc(sizeof(future_cards_t));
  fc->decks = malloc(sizeof(deck_t));
  //make struct for deck
  deck_t * dfc1 = malloc(sizeof(deck_t));
  dfc1->cards = malloc(sizeof(card_t*));
  dfc1->cards[0] = spot1;
  dfc1->n_cards = 1;
  //assign fc to struct
  fc->decks[0] = *dfc1;
  fc->n_decks = 1;

  printf("wow: %d\n", spot2->value);
  printf("wow: %d\n", spot3->value);
  //takes future cards struct that i have to make, index, and ptr to empty card
  add_future_card(fc, 1, spot1);

  //===TEST2===
  printf("===TEST2===\n");
  future_cards_from_deck(test2, fc);

  int x = 2;
  printf("cool: %d\n", x);

  //===TEST3===
  printf("===TEST3===\n");

  if ( argc != 2 ){
    fprintf(stderr, "USAGE: program_name input_file\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if ( f == NULL ){
    fprintf(stderr, "ERROR: could not open file\n");
    return EXIT_FAILURE;
  }

  size_t n_hands = 0;
  future_cards_t * fc2 = malloc(sizeof(future_cards_t));
  fc2->decks = malloc(sizeof(deck_t));
  
  deck_t ** read = malloc(sizeof(deck_t*));
  read = read_input(f, &n_hands, fc2);

  printf("read: %zu\n", read[0]->n_cards);

  if ( fclose(f) != 0 ){
    perror("ERROR: could not close file\n");
    return EXIT_FAILURE;
  }
  //===FREES
  free(dfc1->cards);
  free(dfc1);
  //free(fc->decks[0].cards);
  free(fc->decks[1].cards);
  //free(fc->decks[1]);
  free(fc->decks);
  free(fc);
  
  //--might need to change this if ans changes or becomes an array of arrays
  for ( int i = 0; i < 52; i++){
    if ( deck_contains(ans, *cards[i]) == 0 ){
      free(cards[i]);
    }
  }
  free_deck(ans);
  free(cards);
  return EXIT_SUCCESS;
}
