#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //find length of string
  char * spot = str;
  int count = 0;
  while (*spot != '\0'){
    count++;
    spot++;
  }
  //reverse string
  printf("input is: %s\n", str);
  printf("length is %d\n",count);
  int divNum = count/2; //want integer division to ignore middle of odd lengthed strings
  printf("divNum: %d\n", divNum);
  printf("swap is: \n");
  char swap;
  char temp;
  count -= 1;
  for (int i = 0; i < divNum; i++){
    swap = str[count - i];
    temp = str[i];
    printf("swap: %c\n", swap);
    //move to end of string
    str += (count - i);
    printf("str[count-%d]: %c\n",i, *str);
    //replace value at end of string with temp
    *str = temp;
    printf("new str[count-%d]: %c\n", i, *str);
    //move back to start of string
    str -= (count -i);
    str += i;
    printf("str[%d]: %c\n",i, *str);
    //replace start of string with swap
    *str = swap;
    printf("new str[%d]: %c\n", i, *str);
    //print intermadiate string
    printf("string: %s\n\n", str);
    //return counter to zero
    str -= i;
  }
  printf("%s\n", str);
  
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    printf("\nATTEMPT %d\n", i);
    reverse(array[i]);
    //printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
