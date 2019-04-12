#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


kvpair_t parseString(char * line){
  kvpair_t pair;
  //search for = in line
  //split key from value and save each in to an array
  pair.key = strtok(line, "=");
  if ( pair.key == NULL){
    fprintf(stderr, "ERROR: key value file has incorrect format (missing =)\n");
    exit(EXIT_FAILURE);
  }
  pair.value = strtok(NULL, "");
  //printf("pair value: %s \n",pair.value);
  //replace new line at end of value with \0
  pair.value[strlen(pair.value)-1] = '\0';
  return pair;  
}

kvarray_t * parseFile(FILE * f){
  //takes a key file and returns the kv pairs
  size_t size = 0;
  ssize_t len = 0;
  char * line = NULL;
  static kvarray_t pairs;
  pairs.pairArray = NULL;
  int i = 0;
  while ( (len = getline(&line, &size, f)) >= 0  ){
    //realloc pairs array to fit new key/value pairs
    pairs.pairArray = realloc(pairs.pairArray, (i+1)*sizeof(*(pairs.pairArray)));
    pairs.pairArray[i] = parseString(line);
    line = NULL;
    i++;
  }
  pairs.length = i;
  free(line);

  return &pairs;
}


kvarray_t * readKVs(const char * fname) {
  //open the file and read the lines //split the lines in to key/value pairs (strchr?)
  //add the pairs to an array (realloc)
  //close the file //return an array

  //open file
  FILE * f = fopen(fname, "r");
  if ( f == NULL){
    fprintf(stderr, "ERROR: unable to open file, %s\n", fname);
    exit(EXIT_FAILURE);
  }

  //get kv pairs from key file
  kvarray_t * pairs = parseFile(f);
  
  //close file
  if ( fclose(f) != 0){
    perror("ERROR: Could not close file\n");
    exit(EXIT_FAILURE);
  }
  return  pairs;
}

void freeKVs(kvarray_t * pairs) {
  //clear all the memory allocated by readKVs
  for (int i = 0; i < pairs->length; i++){
    //free memory allocated for each string by getline()
    free(pairs->pairArray[i].key);
    pairs->pairArray[i].key = NULL;
  }
  //free the array that held the strings
  free(pairs->pairArray);
}

void printKVs(kvarray_t * pairs) {
  //This function prints the kv pairs in an array
  for (int i = 0; i < pairs->length; i++){
    printf("key = '%s' value = '%s' \n", pairs->pairArray[i].key, pairs->pairArray[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //This function searches a kv pair array for a specific key
  //if the key is found, the corresponding value is returned. if not it returns NULL
  for (int i = 0; i < (pairs->length-1); i++){
    if ( strcmp(pairs->pairArray[i].key, key) == 0){
      return pairs->pairArray[i].value;
    }
  }
  return NULL;
}
