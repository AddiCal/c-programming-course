#include <stdio.h>
#include <stdlib.h>

int max( int num1, int num2){
  if ( num1 > num2){
    return num1;
  }
  else {
    return num2;
  }
}

int isBetween(int x, int num1, int num2){
      //    ((x is between x_offset  and x_offset +size2) 
  if (x >= num1){
    if (x < num2){
      return 1;
    }
    else {
      return 0;
    }
  }
  else{
    return 0;
  }
}

int isEqual(int x, int num1, int num2){
//     y is equal to either y_offset OR y_offset + size2 - 1 )
  if ( (x==num1) || (x==num2)){
      return 1;
    }
  else {
    return 0;
  }
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  int xplus = x_offset + size2;
  int yplus = y_offset + size2;
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, xplus);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, yplus);
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y<h; y++){
    //count from 0 to w. Call the number you count with x
    for (int x = 0; x<w; x++){
      //check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND 
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *
       if ( ( (isBetween(x, x_offset, xplus)) && (isEqual(y, y_offset, yplus-1))) || ((isBetween(y, y_offset, yplus)) && (isEqual(x, x_offset, xplus-1))) ){
      // if ( (((x>x_offset) && (x<(x_offset + size2))) && ( y==y_offset || y==(y_offset+size2-1)) )  || (((y>y_offset)&&(y<(y_offset+size2-1))) && (x==x_offset || x==(x_offset+size2-1))) ){
	printf("*");
      }

      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #
      else if ( ((x<size1) && (y==0 || y==(size1-1))) || ((y<size1) && (x==0 || x== (size1-1)))){
	printf("#");
      }

      //else print a space
      else {
	printf(" ");
      }
    //when you finish counting x from 0 to w, 
    //print a newline
    }
    printf("\n");
  }

}
