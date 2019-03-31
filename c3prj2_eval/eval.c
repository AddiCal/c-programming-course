#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  //qsort takes an array of cards to sort
  //the inputs to this function are pointers to the two array elements to be compared (card structs)
  const card_t * const * cp1 = vp1;//given a pointer to array elements that point to a struct
  const card_t * const * cp2 = vp2;
  if ( (*cp2)->value == (*cp1)->value){//if values are the same, compare suits
    if ( (*cp2)->suit == (*cp1)->suit ){//if the suits are the same, and value is the same, return 0
	return 0;
      }
    return (*cp2)->suit - (*cp1)->suit;//otherwise sort by value club<diamond<heart<spade
  }
  return (*cp2)->value - (*cp1)->value; //inverted to sort in descending order
}

suit_t flush_suit(deck_t * hand) {
  //determines if a flush exists, if not it returns NUM_SUITS
  //5 cards of any value, same suit
  //assume hand is already sorted by value?
  int spade=0; //3
  int club=0; //0
  int diamond=0; //1
  int heart=0; //2

  //this should work but you should really clean this up later
  //find out how many of each suit we have
  for (int i = 0; i < (hand->n_cards); i++){
    if ((hand->cards[i]->suit) == CLUBS){
      club++;
    }
    else if ((hand->cards[i]->suit) == DIAMONDS){
      diamond++;
    }
    else if ((hand->cards[i]->suit) == HEARTS){
      heart++;
    }
    else if ((hand->cards[i]->suit) == SPADES){
      spade++;
    }
  }

  //find out if we have 5 of any one suit and return that suit
  if ( (spade==5) ){
    return SPADES;
  }
  else if ( heart==5 ){
    return HEARTS;
  }
  else if ( diamond==5){
    return DIAMONDS;
  }
  else if ( club==5 ){
    return CLUBS;
  }
  else{
    return NUM_SUITS;
  }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  //find the largest element in the array
  //set largest to the first element
  unsigned largest=arr[0];
  //replace largest with larger array elements as they arise
  for (int i = 1; i < n; i++) {
    if (arr[i] > largest){
      largest = arr[i];
    }
  }
  return largest;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  //return the lowest index of the value n_of_a_kind in the array match_counts
  for (int i = 0; i < n; i++){
    if (match_counts[i] == n_of_akind){
      return i;
    }
  }
  //if it can't find a match, return exit failure
  return -1;
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  //find a card with:
  //1. match_count>1
  //2. card value is not the same as the value of the card at idx
  //3. the lowest index meeting the first two criteria
  int new_value;
  int match_value = (hand->cards[match_idx]->value);
  for (int i = 0; i < (hand->n_cards); i++){
    //look for a pair with a different value than the first
    if ( match_counts[i] > 1 ){
      new_value = (hand->cards[i]->value);
      if ( (new_value != match_value) ){
	return i;
      }
    }
  }
  return -1;
}

int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n){
  //check first value suit matches fs
  if ( ((hand->cards[index]->suit) != fs) && (fs != NUM_SUITS) ){
    return 0;
  }
  //loop through hand starting at index
  int count = 1;
  int current;
  int next;
  for (int i = index; i < (hand->n_cards - 1); i++){
    //check that value decreases by 1
    current = hand->cards[i]->value;
    next = hand->cards[i+1]->value;
    if ((next) == ( (current) - 1)){
      //check that suit matches
      if ( ((hand->cards[i+1]->suit) == fs) || (fs == NUM_SUITS) ){
	count++; 
      }
    }
    //keep going if there's a duplicate card
    else if (next == current){
      continue;
    }
    else {
      //no straight at index
      break;
    }
    //return 1 if straight of length n at index is present
    if (count == n){
      return 1;
    }
  }
  //return 0 if straight of length n at indes is not present
  return 0;
}

int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs){
  //search for 5,4,3,2 straight
  int straight;
  for (int i = 0; i < hand->n_cards; i++){
   straight = is_n_length_straight_at(hand, i, fs, 4);
   if ( straight == 1 && hand->cards[i]->value == 5){
     for (int i = 0; i < 4; i++){
       if ( hand->cards[i]->value==14 && (hand->cards[i]->suit==fs || fs==NUM_SUITS)){
	 //ace low straight present
	 return 1;
       }
     }
   }
  }
  /*
  //straight is 1 for true, 0 for false
  int straight = is_n_length_straight_at(hand, index, fs, 4);
  if ( straight == 1 && hand->cards[index]->value == 5){
    for (int i = 0; i < 4; i++){
      if ( hand->cards[i]->value==14 && (hand->cards[i]->suit==fs || fs==NUM_SUITS)){
	//ace low straight present
	return 1;
      }
    }
  }
  */
  //no ace low straight
  return 0;
}


int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  //looks for a straight in the hand starting at the given index
  //fs tells you the suit it should look for if any
  //hand is sorted in to descending order A = 14
  //return -1 for ace low straight, 0 for no straight, 1 for other straights
  //card_t count;

  //1 for true, 0 for false
  int reg_straight = is_n_length_straight_at(hand, index, fs, 5);
  //1 for true, 0 for false
  int ace_straight = is_ace_low_straight_at(hand, index, fs);

  //regular straight present
  if (reg_straight == 1){
    return 1;
  }
  //ace stright present
  if (ace_straight == 1){
    return -1;
  }
  //no straights
  return 0;
}


hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  //make hand_eval_t, ranking is what value, n cards starting at index idx in to cards array
  //used only for the first n_of_akind finds, the second pair will be found later

  //**add aserts for other rankings!!
  assert(what>0); //can't be nothing
  hand_eval_t ans;
  
  ans.ranking = what;
  
  //fill in first n cards of ans with nofakind from hand
  //cycle through cards in hand
  int ind = 0;
  for (int i = 0; i < hand->n_cards; i++){
    //isloate cars corresponding to nofakind
    if ( i>=idx && i<(idx+n)){
      ans.cards[ind] = hand->cards[i];
      ind++;
      if (ind == n){
	break;
      }
    }
  }
  //!!Hand can have more than 5 cards!
  //fill the remaining cards in ans with the next highest cards of hand
  //cycle through cards in hand
  ind = n;
  for (int i = 0; i < hand->n_cards; i++){
    //isloate cars NOT corresponding to nofakind
    if ( i<idx || i>=(idx+n)){
      ans.cards[ind] = (hand->cards[i]);
      ind++;
      if (ind == 5) {
	break;
      }
    } 
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  //return +1 if hand 1 wins, -1 if hand 2 wins, 0 for tie
  
  //a. sort hands with qsort
  qsort( (hand1->cards), (hand1->n_cards), sizeof(hand1->cards[0]), card_ptr_comp);
  qsort( (hand2->cards), (hand2->n_cards), sizeof(hand2->cards[0]), card_ptr_comp);
  
  //b. call evaluate_hand on each hand
  hand_eval_t h1;
  h1 = evaluate_hand(hand1);
  hand_eval_t h2;
  h2 = evaluate_hand(hand2);

  //c. decide which hand winds based on their ranking
  if ((h1.ranking) > (h2.ranking)){
    //h1 wins
    return 1;
  }
  else if ((h1.ranking) < (h2.ranking)){
    //h2 wins
    return -1;
  }
  
  //d. if the rankings tie you'll have to compare the tie breaking cards
  if ((h1.ranking) == (h2.ranking)){
    for (int i = 0; i < 5; i++){
      if ( (h1.cards[i]->value) > (h2.cards[i]->value) ){
	//h1 wins
	return 1;
      }
      else if ( (h1.cards[i]->value) < (h2.cards[i]->value) ){
	//h2 wins
	return -1;
      }
    }
  }
  //hands are tied
  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
