#include "cards.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  //test ranking_to_string fxn
  printf("testing ranking_to_string\n");
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
  printf("\ntesting value_letter\n");
  card_t test_cards;
  test_cards.value = 0;
  test_cards.suit = 0;
  for (int i=2; i<15; i++){
    test_cards.value = i;
    printf("%c\n",value_letter(test_cards));
  }
  

  //test suit_letter fxn
  printf("\ntesting suit_letter\n");
  for (int i=0; i<4; i++){
    test_cards.suit = i;
    printf("%c\n",suit_letter(test_cards));
  }
  
  //test print_card fxn
  printf("\ntesting print_card\n");

  printf("value 14 suit 0\n");
  test_cards.value = 14;
  test_cards.suit = 0;
  print_card(test_cards);

  printf("value 2 suit 1\n");
  test_cards.value = 2;
  test_cards.suit = 1;
  print_card(test_cards);

  printf("value 10 suit 2\n");
  test_cards.value = 10;
  test_cards.suit = 2;
  print_card(test_cards);

  printf("value 9 suit 3\n");
  test_cards.value = 9;
  test_cards.suit = 3;
  print_card(test_cards);

  
  //test card_from_letters fxn
  printf("\ntesting card_from_letters\n");
  test_cards = card_from_letters('3', 'h');
  printf("input(3,h)\n");
  print_card(test_cards);
  
  test_cards = card_from_letters('K', 'd');
  printf("input(K,d)\n");
  print_card(test_cards);
  
  test_cards = card_from_letters('A', 'c');
  printf("input(A,c)\n");
  print_card(test_cards);

  test_cards = card_from_letters('0', 's');
  printf("input(0,s)\n");
  print_card(test_cards);

  test_cards = card_from_letters('K', 'c');
  printf("input(K,c)\n");
  print_card(test_cards);

  test_cards = card_from_letters('0', 'd');
  printf("input(0,d)\n");
  print_card(test_cards);


  
  //test card_From_num fxn
  printf("\ntesting card_from_num\n");
  for (int i=0; i<52; i++){
    test_cards = card_from_num(i);
    print_card(test_cards);
  }
  
  
}
