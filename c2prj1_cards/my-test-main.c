#include "cards.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  //test ranking_to_string fxn
  ranking_to_string(0);
  ranking_to_string(1);
  ranking_to_string(2);
  ranking_to_string(3);
  ranking_to_string(4);
  ranking_to_string(5);
  ranking_to_string(6);
  ranking_to_string(7);
  ranking_to_string(8);
  //ranking_to_string(-2);
  //ranking_to_string(9);
  
  //test value_letter fxn
  card_t test_cards;
  test_cards.value = 0;
  test_cards.suit = 0;
  for (int i=2; i<15; i++){
    test_cards.value = i;
    printf("%c\n",value_letter(test_cards));
  }
  

  //test suit_letter fxn
  for (int i=0; i<4; i++){
    test_cards.suit = i;
    printf("%c\n",suit_letter(test_cards));
  }
  
  //test print_card fxn
  test_cards.value = 14;
  test_cards.suit = 0;
  print_card(test_cards);
  
  test_cards.value = 3;
  test_cards.suit = 1;
  print_card(test_cards);
  
  test_cards.value = 10;
  test_cards.suit = 2;
  print_card(test_cards);
  
  test_cards.value = 9;
  test_cards.suit = 3;
  print_card(test_cards);

  
  //test card_from_letters fxn
  test_cards = card_from_letters('3', 'h');
  printf("input(3,h)\n");
  printf("value: %d, suit: %d\n", test_cards.value, test_cards.suit);
  //test_cards = card_from_letters('h', '3');
  //printf("value: %d, suit: %d\n", test_cards.value, test_cards.suit);
  test_cards = card_from_letters('K', 'd');
  printf("input(K,d)\n");
  printf("value: %d, suit: %d\n", test_cards.value, test_cards.suit);
  test_cards = card_from_letters('A', 'c');
  printf("input(A,c)\n");
  printf("value: %d, suit: %d\n", test_cards.value, test_cards.suit);
  test_cards = card_from_letters('Q', 's');
  printf("input(A,s)\n");
  printf(" value: %d, suit: %d\n", test_cards.value, test_cards.suit);
  test_cards = card_from_letters('J', 'h');
  printf("input(J,h)\n");
  printf("value: %d, suit: %d\n", test_cards.value, test_cards.suit);

  
  //test card_From_num fxn
  for (int i=0; i<52; i++){
    test_cards = card_from_num(i);
    print_card(test_cards);
  }
  
  
}
