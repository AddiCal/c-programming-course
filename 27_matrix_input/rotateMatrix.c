#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void transpose(char matrix[10][10]){
  char temp1;
  for (int i=0; i<10; i++){
    for (int j=0; j<10; j++){
      if (j > i){
	temp1 = matrix[i][j];
	matrix[i][j] = matrix[j][i];
	matrix[j][i] = temp1;
      }
    }
  }
}

void reverse(char matrix[10][10]){
  char swap;
  int count = 10-1;
  for (int i=0; i<10; i++){
    for (int j=0; j<5; j++){
      swap = matrix[i][j];
      matrix[i][j] = matrix[i][count-j];
      matrix[i][count-j] = swap;
    }
  }
}

void rotate(char matrix[10][10]){
  //transpose and then reverse rows
  transpose(matrix);
  reverse(matrix);
}


int rotateMatrix(FILE * f){
  char matrix[10][10] = {0};
  //read data from file
  //copy data to matrix
  //ensure that data read is legal chars
  //ensure that data read is 10char+\n
  
  int c;
  int row=0;
  int col=0;
  int counter=0;
  while ( (c = fgetc(f)) != EOF ){
    if ( c == '\n'){
      continue;
    }
    //should probably use strchr or something to make sure each row is 10 char and \n
    if ( c ){
      //column ranges from 0-9 per row
      col = counter%10;
      matrix[row][col] = c;
      counter++;
      //row increments by 1 each time column reaches 9
      if (col == 9){
	row++;
      }
    }  
  }
  
  rotate(matrix);

  //print rotated matrix to stdout
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      fprintf(stdout, "%c", matrix[i][j]);
    }
    //print new line every 10th car
    fprintf(stdout, "\n");
  }
  
  return EXIT_SUCCESS;
}

int checkFile(FILE * f){
  //makes sure file has the correct format?
  char line[12];
  int count=0;
  while ( fgets(line, sizeof(line),f) != NULL  ){
    for ( int i = 0; i < 10; i++ ){
      if( isprint(line[i]) == 0){
	fprintf(stderr, "ERROR: non printable carachter present, row %d, col %d\n", count, i);
      }
    }
    //check that each line has a newline at the 10th char
    if ( line[10] != '\n'){
      fprintf(stderr, "ERROR: missing newline at index 10, row %d too long or short\n", count);
      return EXIT_FAILURE;
    }
    count++;
  }
  //check that there is the correct number of rows
  if ( count != 10 ){
    fprintf(stderr, "ERROR: incorrect number of rows, there must be 10, there are %d\n", count);
    return EXIT_FAILURE;
  }
  //reset stream to start of file
  fseek(f, 0, SEEK_SET);
  
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv){
  //takes file as input so argv[2]

  //check for correct number of arguments
  if ( argc != 2){
    fprintf(stderr, "Usage: rotateMatrix inputfile\n");
    return EXIT_FAILURE;
  }
  //indexing argv starts at 0
  FILE * f = fopen(argv[1], "r");
  if ( f == NULL){
    fprintf(stderr, "ERROR: file could not be opened\n");
    return EXIT_FAILURE;
  }

  if ( checkFile(f) ){
    return EXIT_FAILURE;
  }

  //checkFile(f);

  rotateMatrix(f);

  //close file
  if ( fclose(f) != 0){
    perror("Unable to close input file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
