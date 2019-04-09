#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
//sorts an array of strings, count is the length of the array
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void  printArray(FILE * f){
  //takes in file, dynamically allocates each line to an array element, returns array
  size_t size = 0;
  //size_t length = 0;
  char * line = NULL;
  char ** array = NULL;
  int i = 0;
  //lenth = the length of the string read in by get line
  //size = the number of boxes allcoated to hold the string
  //line = a pointer to the start of the string
  while ( getline(&line, &size, f) >=0 ){
    //getline writes a string from f to line
    //this reallocates the null array to have as many elements as there are rows in the file
    array = realloc(array, (i+1)*sizeof(*array));
    //this assigns each element of the array to the newest line
    array[i] = line;
    //this clears line so that we can write the next line to it without any weirdness
    line = NULL;
    //increments the counter
    i++;
  }
  free(line);
  //sort array
  sortData(array, i);

  //print data
  for ( int j = 0; j < i; j++){
    printf("%s", array[j]);
  }
  free(array);
}

int main(int argc, char ** argv) {
  
  //if argc == 1: read from stdin, pass each line in to the array, sort the array, print the results, free memory, exit
  //if argc > 1: read from each input file, pass each line in to the array (one file at a time),
  //  sort the array, print the result, free memory and exit
  if ( argc == 1 ){
    //open file or return error
    FILE * f = stdin;
    if ( f == NULL){
      fprintf(stderr, "ERROR: could not open file\n");
      return EXIT_FAILURE;
    }
    //get an array holding each line from stdin and sort it and print it
    printArray(f);
  }

  if ( argc > 1){
    // loop through file names provided
    for ( int i = 1; i < (argc); i++){
      //open file or return error
      FILE * f = fopen(argv[i], "r");
      if ( f == NULL){
	fprintf(stderr, "ERROR: could not open file\n");
	return EXIT_FAILURE;
      }
      
      printArray(f);
    }
  }
  
  return EXIT_SUCCESS;
}
