#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans, int caseNum){
  if ( power(x,y) != expected_ans){
    printf("ERROR: failed Case #%d\n", caseNum);
    exit(EXIT_FAILURE);
  }
}

int main(){
  //Test Cases
  int x;
  int y;
  int expected_ans;

  //regular case
  printf("Case 1\n");
  x=2;
  y=6;
  expected_ans = 64;
  run_check(x, y,  expected_ans, 1);
  
  //y is a large number
  printf("Case 2\n");
  x=2;
  y=30;
  unsigned long exp_ans = 1073741824;
  run_check(x, y,  exp_ans, 2);
  
  //negative number
  /*printf("Case 3\n");
  x=-5;
  y=3;
  expected_ans = 0;
  run_check(x, y,  expected_ans, 3);
  */

  //y=0
  printf("Case 4\n");
  x=22;
  y=0;
  expected_ans = 1;
  run_check(x, y,  expected_ans, 4);
  
  //x=0
  printf("Case 5\n");
  x=0;
  y=5;
  expected_ans = 0;
  run_check(x, y,  expected_ans, 5);
  
  //both are 0
  printf("Case 6\n");
  x=0;
  y=0;
  expected_ans = 1;
  run_check(x, y,  expected_ans, 6);
  
  //x is double/float
  printf("Case 7\n");
  double X=3.4;
  y=3;
  //double expAns = 39.304;
  expected_ans = 27; //assume function will truncate
  run_check( X, y,  expected_ans, 7);
  
  //y is a double/float
  printf("Case 8\n");
  x=3;
  double Y=2.7;
  expected_ans = 9; //assume function will truncate
  run_check(x, Y,  expected_ans, 8);
  
  //x is 1
  printf("Case 9\n");
  x=1;
  y=3;
  expected_ans = 1;
  run_check(x, y,  expected_ans, 9);
  
  //y is 1
  printf("Case 10\n");
  x=9;
  y=1;
  expected_ans = 9;
  run_check(x, y,  expected_ans, 10);
  
  
  return EXIT_SUCCESS;
}
