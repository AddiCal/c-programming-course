#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  //allocate memory for counts_t struct and initialize it to 0 counts
  //one_count_t has char*name and int count
  //counts_t has one_count_t * array and int length
  static counts_t count;
  count.array = malloc(1*sizeof(*(count.array)));
  count.length = 0;
  count.unknown = 0;
  
  return &count;
}


void addCount(counts_t * c, const char * name) {
  //increment the count for the corresponding name //NULL represents a return of unknown
  //adds elements to counts array if it doesn't exist
  
  //if null, increment unknown counter
  if ( name == NULL){
    c->unknown++;
  }
  //otherwise check that name exists in c, and if not add it
  else{
    //if length is 0 the array is empty and this name should be added as element 1
    if ( c->length == 0){
      c->array[0].title = name;
      c->array[0].count = 1;
      c->length = 1;
    }
    //otherwise, check if name appears in array and increment counter
    else{
      int added = 0;
      for ( int i = 0; i < c->length; i++){
	if ( strcmp(name, c->array[i].title) == 0 ){
	  c->array[i].count++;
	  added = 1;
	}
      }
      //if the name didn't match any entries in the list, add it to the list
      if ( added == 0 ){
	c->array = realloc(c->array, (c->length+1)*sizeof(*(c->array)));
	c->array[c->length].title = name;
	c->array[c->length].count = 1;
	c->length++;
      }
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //takes a counts_t and prints the info to a file
  //<unknown> should appear last if it exists
  for (int i = 0; i < c->length; i++){
    fprintf(outFile, "%s: %d\n", c->array[i].title, c->array[i].count);
  }
  if (c->unknown > 0){
    fprintf(outFile, "<unknown> : %d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //free memory associated with counts_t
  free(c->array);
}
