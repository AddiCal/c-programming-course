#include <stdio.h>
#include <stdlib.h>

//Retirement struct
struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;


//Balace fxn
double balance(int age, double balance,retire_info desired){
  //"Age %3d month %2d you have $%.21f\n"(age in years,months, balance)
  //balance+(balance*rate)+contribution
  printf("Age %3d month %2d you have $%.2f\n", age/12, age%12, balance);
  double addition = (balance*desired.rate_of_return) + desired.contribution;
  balance += addition;
  return balance;
}

//Retirement fxn
void retirement(int startAge, double initial, retire_info working, retire_info retired){
  //calculate balance for each working month
  double cur_balance;
  int done_work=startAge+working.months;
  int done_retirement=done_work+retired.months;
  cur_balance = initial;
  for (int i=startAge; i<(done_work); i++){
    cur_balance = balance(i, cur_balance, working);
  }
  //calculate balance for each retired month
  for (int i=(done_work); i<(done_retirement); i++){
    cur_balance = balance(i, cur_balance, retired);
  }
}

int main(){
  int startAge = 327; //in months
  int initial = 21345; //in dollars

  //working struct
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12.0;

  //retirement struct
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12.0;

  //run calculator
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
