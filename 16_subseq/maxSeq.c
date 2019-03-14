#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  //if array is empty, return none
  if (n ==0){
    return 0;
  }
  int seqCount = 1;
  int largestCount = 1;
  int step = array[0];
  for (int i=1; i<n; i++){
    //compare i to i+1, if i+1 is larger increase count
    if (step < array[i]){
      seqCount ++;
      //compare count to largest count, if count is larger update largest count
      if (seqCount > largestCount){
	largestCount = seqCount;
      }
    }
    //if i+1 is not larger than i, reset the sequence counter, leave largest count
    else {
      seqCount = 1;
    }
    //step ahead one element in array
    step = array[i];
  }
  
  return largestCount;
}
