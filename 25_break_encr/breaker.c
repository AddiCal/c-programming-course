#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int max(int * array, int n){
  //find the maximum value in an array of length n, return index
  int maxval = array[0];
  int maxidx = 0;
  for (int i = 1; i < n; i++){
    if( array[i] > maxval){
      maxval = array[i];
      maxidx = i;
    }
  }
  return maxidx;
}

int decrypt(FILE * f) {    
  int c;
  int alphabet[25]={0};
  int a = 'a';
  int e = 'e';
  int hold=0;
  //count which character occurs most often
  while ((c = fgetc(f)) != EOF) {        
    if (isalpha(c)) {
      c = tolower(c);
      //for each letter, add 1 to it's corresponding place in the alphabet
      hold = alphabet[c-a];
      hold++;
      alphabet[c-a] = hold;
      //clear hold for each new iteration
      hold = 0;
    }            
  }
  
  //find index of largest number in alphabet array (0 to 25)
  int maxletter = max(alphabet, 25);
  //index of e is 4
  int eindex = e - a;
  int diff = maxletter - eindex;

  if ( diff == -1){
    diff = 25;
  }
  else if ( diff == -2){
    diff = 24;
  }
  else if ( diff == -3){
    diff = 23;
  }
  else if ( diff == -4){
    diff = 22;
  }

  //return error if maxletter index is less than 4
  if ( diff < -4 ){
    fprintf(stderr, "ERROR: max letter less than e index\n");
    return EXIT_FAILURE;
  }
  
  //print decryption key to stdout
  printf("%d\n", diff);
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  //check that only two arguments are present
  if (argc != 2) {    
    fprintf(stderr,"Usage: encrypt inputFileName\n");    
    return EXIT_FAILURE;  
  }  

  //open the input file if possible
  FILE * f = fopen(argv[1], "r");  
  if (f == NULL) {    
    perror("Could not open file");    
    return EXIT_FAILURE;  
  }

  //decrypt the text
  decrypt(f);

  //close the file if possible
  if (fclose(f) != 0) {    
    perror("Failed to close the input file!");    
    return EXIT_FAILURE;  
  }
  
  return EXIT_SUCCESS;
}
