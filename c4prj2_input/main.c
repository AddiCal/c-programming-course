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
    if ( deck->cards[i]->suit == NUM_SUITS ){
      printf("?? ");
      continue;
    }
    print_card(*(deck->cards[i]));
    printf(" ");
  }
  printf("\n");
}

void print_fc(future_cards_t * fc){
  printf("fc->n_decks: %zu\n", fc->n_decks); 
  for (int i = 0; i < fc->n_decks; i++){
    if ( fc->decks[i].cards[0]->suit == NUM_SUITS ) {
      continue;
    }
    printf("index: %d", i);
    print_deck(&(fc->decks[i]));
  }
}

int main( int argc, char ** argv){
  //built test deck and add empty cards
  //==array of 52 cards
  card_t ** cards = malloc(52*sizeof(card_t*));
  //==deck of cards used to add empty cards
  int len = 10;
  int ans_size = 1010;
  deck_t * ans = malloc(sizeof(deck_t));
  ans->cards = malloc(ans_size*sizeof(card_t*));
  //==secondary deck of cards used to fill fc
  deck_t * test2 = malloc(sizeof(deck_t));
  test2->cards = malloc(len*sizeof(card_t*));

  //fill in the decks with 5 cards
  int k = 0;
  for ( int i = 0; i < 13; i++ ){
    for ( int j = 0; j < 4; j++ ){
      cards[k] = malloc(sizeof(card_t));
      *cards[k] = card_from_num(i+13*j);
      k++;
    }
  }

  for ( int i = 0; i < len; i++){
    //ans->cards[i] = cards[(i+3)*(4)];
    test2->cards[i] = cards[(i)*4];
  }
  for ( int i = 0; i < ans_size; i++){
    ans->cards[i] = cards[i%52];
  }
  ans->n_cards = ans_size;
  test2->n_cards = len;

  //print_deck(ans);
  //print_deck(test2);

  //==build fc deck (hold the pointers to each future card in the hands according to their fc index)
  future_cards_t *fc = malloc(sizeof(future_cards_t));
  fc->decks = malloc(sizeof(deck_t));
  fc->decks->cards = malloc(sizeof(card_t*));

  card_t ** empty = malloc(sizeof(card_t*));
  empty[0] = malloc(sizeof(card_t));
  empty[0]->value = 0;
  empty[0]->suit = NUM_SUITS;

  //fc->decks->cards[0] = empty[0];
  //fc->decks->n_cards = 0;
  //fc->n_decks = 0;
  
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
  deck_t ** read = read_input(f, &n_hands, fc);
  
  printf("\n===hands from file: \n");
  for (int i = 0; i < n_hands; i++){
    print_deck(read[i]);
  }

  future_cards_from_deck(ans, fc);

  printf("\n===fc cards filled in\n");
  print_fc(fc);

  printf("\n===ans deck\n");
  print_deck(ans);

  printf("\n===hands filled in with ans: \n");
  for (int i = 0; i < n_hands; i++){
    print_deck(read[i]);
  }
  
  if ( fclose(f) != 0 ){
    perror("ERROR: could not close file\n");
    return EXIT_FAILURE;
  }
  //===FREES
  
  //--might need to change this if ans changes or becomes an array of arrays
  for (int i = 0; i < fc->n_decks; i++){
    free_deck(fc->decks);
  }
  
  for ( int i = 0; i < 52; i++){
    if ( deck_contains(ans, *cards[i]) == 0 ){
      free(cards[i]);
    }
  }
  free_deck(ans);
  free(cards);
  return EXIT_SUCCESS;
}
