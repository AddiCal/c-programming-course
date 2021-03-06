#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  if (!str){
    return;
  }
  //find length of string
  char * spot = str;
  int count = 0;
  while (*spot != '\0'){
    count++;
    spot++;
    /*
    if (count == 10000){
      printf("ERROR: no null terminator found\n");
      exit(EXIT_FAILURE);
    }
    */
  }
  
  //reverse string
  int divNum = count/2; //want integer division to ignore middle of odd lengthed strings
  char swap;
  char temp;
  count -= 1;

  for (int i = 0; i < divNum; i++){
    swap = str[count - i];
    temp = str[i];
    //move to end of string
    str += (count - i);
    //replace value at end of string with temp
    *str = temp;
    //move back to start of string
    str -= (count -i);
    str += i;
    //replace start of string with swap
    *str = swap;
    //return counter to zero
    str -= i;
  }
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
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
