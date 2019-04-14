#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

//i have a list of key  value pairs. i then give my program a list of keys.
//it should check the list for each key and count how many times that key appears
//is should then print the total count of each corresponding value in an output file


counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //open the file, checks if kv pairs from input array appear in the file and creates a counts array
  //the counts array keeps track of how many times the key appeared in the file
  FILE * f = fopen(filename, "r");
  if ( f == NULL){
    fprintf(stderr, "ERROR: could not open file\n");
    exit(EXIT_FAILURE);
  }
  //create counts array
  counts_t * ans = createCounts();

  //get counts from file
  size_t size = 0;
  ssize_t len = 0;
  char * line = NULL;
  int added = 0;
  int j = 0;
  while ( (len = getline(&line, &size, f)) >= 0  ){
    //check whether each line in the file corresponds to a key
    //strip \n from line
    char * new = strtok(line, "\n");
    //strncpy(new, line, strlen(line)-1);
    for ( int i = 0; i < kvPairs->length; i++){
      char * key = kvPairs->pairArray[i].key;
      //if yes, add the value for that key to counts
      if ( strcmp(new, key) == 0){
	//this is keeping track of the values, if wrong change value to line
	addCount( ans, kvPairs->pairArray[i].value );
	added++;
	break;
      }
      
    }
    j++;
    if (added != j){
      addCount( ans, NULL );
      added = j;
    }
    
  }
  free(line);
  if ( fclose(f) != 0 ){
    perror("ERROR: cannot close file!\n");
    exit(EXIT_FAILURE);
  }
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3){
    //argv[0] = prog name, argv[1] = kvFile, argv[2]+ = keyFiles
    fprintf(stderr, "Minimum usage: kvPairFile keyFile1 keyFile2 ect.\n");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  
 //count from 2 to argc (call the number you count i)
  for ( int i = 2; i < argc; i++){ 
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if ( f == NULL){
      fprintf(stderr, "ERROR: cannot open file\n");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if ( fclose(f) != 0 ){
      perror("Could not close file!\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }

 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
