#include <stdio.h>
#include <stdlib.h>

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
