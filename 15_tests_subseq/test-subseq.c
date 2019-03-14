#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);



int printArray(int *array, size_t n){
  if (n==0){
    printf("NULL array\n");
    return 1;
  }
  printf("test array = { ");
  for (int i=0; i<n; i++){
    printf("%d, ", array[i]);
  }
  printf(" }\n");
  return 0;
}

int main(){
  //Test Cases
  //increasing list
  int array0[] = {1, 2, 4, 6, 7, 9, 10};
  if (maxSeq(array0, 7) != 7){
    printf("failed on array0\n");
    exit(EXIT_FAILURE);
  }
  //empty list
  int array1[] = {};
  if (maxSeq(array1, 0) != 0){
    printf("failed on array1\n");
    exit(EXIT_FAILURE);
  }
  //decreasing list
  int array2[] = {10, 8, 7, 4, 1};
  if (maxSeq(array2, 5) != 1){
    printf("failed on array2\n");
    exit(EXIT_FAILURE);
  }
  //single element
  int array3[] = {244};
  if (maxSeq(array3, 1) != 1){
    printf("failed on array3\n");
    exit(EXIT_FAILURE);
  }
  //equal length sequences
  int array4[] = {1, 2, 50, 53, 40, 42, 43, 45};
  if (maxSeq(array4, 8) != 4){
    printf("failed on array4\n");
    exit(EXIT_FAILURE);
  }
  //long sequence before short one
  int array5[] = {20, 24, 36, 57, 10, 21};
  if (maxSeq(array5, 6) != 4){
    printf("failed on array0\n");
    exit(EXIT_FAILURE);
  }
  //negative numbers
  int array6[] = {-2, -100, -53, -10, 20};
  if (maxSeq(array6, 5) != 4){
    printf("failed on array6\n");
    exit(EXIT_FAILURE);
  }
  //same number
  int array7[] = {3, 3, 3, 3, 3};
  if (maxSeq(array7, 5) != 1){
    printf("failed on array7\n");
    exit(EXIT_FAILURE);
  }
  //multiple sequences
  int array8[] = {80, 99, 256, 200, 300, 1000000, 12, 84, 96, 32810312, 222222, 43};
  if (maxSeq(array8, 12) != 4){
    printf("failed on array8\n");
    exit(EXIT_FAILURE);
  }
  //sequence with zero
  int array9[] = {3, 99, 2344, 8, 12, 0, 33, 89, 500, 796};
  if (maxSeq(array9, 10) != 5){
    printf("failed on array9\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
