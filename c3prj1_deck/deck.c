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

//======PROJECT 4 CODE===========

void add_card_to( deck_t * deck, card_t c){
  //add a particular card to a given deck (realloc)
  //deck_t has card_t **cards, size_t n_cards
  //card_t has uint value, suit_t suit
  card_t *card = malloc(sizeof(card_t));
  card[0] = c;
  int newLen = deck->n_cards + 1;
  deck->cards = realloc(deck->cards, newLen*sizeof(card_t *));
  deck->cards[newLen-1] = &card[0];
  printf("added: value: %d, suit: %d\n", deck->cards[deck->n_cards]->value, deck->cards[deck->n_cards]->suit);
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck){
  //adds an empty card (value 0, suit 0) to a deck and returns a pointer to it
  static card_t empty;
  empty.value = 0;
  empty.suit = NUM_SUITS;
  add_card_to(deck, empty);
  card_t * ans = deck->cards[deck->n_cards-1];
  return ans;
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  //creates a full deck minus the cards in excluded_cards
  //use card_from_num and deck_contains
  //0-12 hearts, 13-25 diamonds, 26-38 clubs, 39-51 spades 
  static card_t *smallDeck;
  int newLen = 52-excluded_cards->n_cards;
  smallDeck = malloc(newLen*sizeof(card_t));
  //card_t smallDeck[newLen];
  
  static deck_t ans;
  ans.cards = malloc(newLen*sizeof(card_t*));
  ans.n_cards = newLen;

  int count = 0;
  int j = 0;
  for ( int i = 0; i < 52; i++){
    card_t c = card_from_num(i);
    if ( deck_contains(excluded_cards, c) == 1 ){
      count++;
      continue;
    }
    else{
      smallDeck[j].value = c.value;
      smallDeck[j].suit = c.suit;
      j++;
    }		      
  }
  //ans.cards = &smallDeck;
  for ( int i = 0; i < newLen; i ++){
    ans.cards[i] = &smallDeck[i];
  }
  printf("excluded count: %d\n", count);
  //free(smallDeck);
  
  return &ans;
}


deck_t * build_remaining_deck( deck_t ** hands, size_t n_hands){
  //build the deck that remains once the hands have been dealt
  //find total number of cards in all hands
  static deck_t allHands;
  int size = 0;
  for ( int i = 0; i < n_hands; i++){
    size += hands[i]->n_cards;
  }
  //group all the cards from all the hands in to one
  int k = 0;
  allHands.cards = malloc(size*sizeof(card_t*));
  allHands.n_cards = size;
  for ( int i = 0; i < n_hands; i++){
    for ( int j = 0; j < hands[i]->n_cards; j++){
      allHands.cards[k] = hands[i]->cards[j];
      k++;
    }
  }
  //biuld deck that remains
  deck_t * ans =  make_deck_exclude(&allHands);
  free(allHands.cards);
  return ans;
}

void free_deck(deck_t * deck){
  //free(deck->cards[deck->n_cards-1]);
  free(deck->cards);
}
