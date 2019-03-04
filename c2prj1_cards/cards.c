#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  //assert stops the program if the statement is false
  //check syntax for card struct
  assert(c.value >= 2);
  assert(c.value <= 14);
  assert(c.suit >= 0);
  assert(c.suit < 4);
}

const char * ranking_to_string(hand_ranking_t r) {
  assert(r>=0);
  assert(r<9);
  switch(r){
  
  case STRAIGHT_FLUSH:
    printf("This is a straight flush\n");
    break;
  case FOUR_OF_A_KIND:
    printf("This is a four of a kind\n");
    break;
  case FULL_HOUSE:
    printf("This is a full house\n");
    break;
  case FLUSH:
    printf("This is a flush\n");
    break;
  case STRAIGHT:
    printf("This is a straight\n");
    break;
  case THREE_OF_A_KIND:
    printf("This is a three of a kind\n");
    break;
  case TWO_PAIR:
    printf("This is a two pair\n");
    break;
  case PAIR:
    printf("This is a pair\n");
    break;
  case NOTHING:
    printf("This is a nothing\n");
    break;
  }
  return "";
}

char value_letter(card_t c) {
  char val = '0'; //10 has value '0'
  assert_card_valid(c);
  if (c.value>1 && c.value<10){
    //for values 2-9
    val += c.value;
  }
  if (c.value == VALUE_ACE){
    val += 17; //'A'=65
  }
  if (c.value == VALUE_KING){
    val += 27; //'K'=75
  }
  if (c.value == VALUE_QUEEN){
    val += 33; //'Q'=81
  }
  if (c.value == VALUE_JACK){
    val += 26; //'J'=74
  }
  return val;
}


char suit_letter(card_t c) {
  assert_card_valid(c);
  char suit;
  switch(c.suit){
  case SPADES:
    suit = 's';
    //return 's';
    break;
  case HEARTS:
    suit = 'h';
    //return 'h';
    break;
  case DIAMONDS:
    suit = 'd';
    //return 'd';
    break;
  case CLUBS:
    suit = 'c';
    //return 'c';
    break;
  default:
    suit = '?';
    //return 'E';
    break;
  }
  return suit;
}

void print_card(card_t c) {
  assert_card_valid(c);
  char suit;
  char value;
  suit = suit_letter(c);
  value = value_letter(c);
  printf("%c%c\n",value,suit);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  //check suit
  assert(suit_let=='c' || suit_let=='h' || suit_let=='d' || suit_let=='s');
  //check value
  int value = ((int) value_let); // 48='0'
  //check absolute bounds
  assert(value>47);
  assert(value<82);
  //values for 0-9, A, J, K, Q
  assert((value>=48 && value<=57) || value==65 || value==74 || value==75 || value==81);
  temp.value = value_let;
  temp.suit = suit_let;
  print_card(temp);
  /*
  switch(suit_let){
  case 's':
    temp.suit = SPADES;
    break;
  case 'h':
    temp.suit = HEARTS;
    break;
  case 'd':
    temp.suit = DIAMONDS;
    break;
  case 'c':
    temp.suit = CLUBS;
    break;
    //default:
    //temp.suit = 20;//something has gone wrong
    //break;
  }
  //default is error case, specified suit wasn't c,d,s, or h
  //assert(temp.suit!=20);
  */
  //convert value
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  assert(c>=0);
  assert(c<52);

  //find suit
  if(c>=0 && c<13){
    temp.suit = HEARTS;
  }
  else if (c>=13 && c<26){
    temp.suit = DIAMONDS;
  }
  else if (c>=26 && c<39){
    temp.suit = CLUBS;
  }
  else if (c>=39 && c<52){
    temp.suit = SPADES;
  }
  else {
    printf("ERROR: invalid card (suit)");
    return temp;
  }

  //find value (with %)
  c +=1;
  switch(c%13){
  case 0:
    temp.value = VALUE_ACE; //10
    break;
  case 1:
    temp.value = 2; //VALUE_ACE;
    break;
  case 2:
    temp.value = 3; //2;
    break;
  case 3:
    temp.value = 4; //3;
    break;
  case 4:
    temp.value = 5; //4;
    break;
  case 5:
    temp.value = 6; //5;
    break;
  case 6:
    temp.value = 7; //6;
    break;
  case 7:
    temp.value = 8; //7;
    break;
  case 8:
    temp.value = 9; //8;
    break;
  case 9:
    temp.value = 10; //9;
    break;
  case 10:
    temp.value = VALUE_JACK;
    break;
  case 11:
    temp.value = VALUE_QUEEN;
    break;
  case 12:
    temp.value = VALUE_KING;
    break;
  }
  
  return temp;
}
