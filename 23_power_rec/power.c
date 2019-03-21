#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y){
  //y=0 for any x will give ans=1
  if ( y == 0){
    return 1;
  }
  return x*power(x, y-1);
}
