#include "date.h"
#include <stdio.h>
#include <stdlib.h>

/* comment out the line below if you DO NOT want the
 * program to validate the input. Switching off the validation
 * might be a security issue, but if the input is trusted, it might
 * speed up program's execution.
 */

struct date{
  int year;
  int month;
  int day;
};

int main(){
  Date* date_year1 = date_create("11/10/1991");
  Date* date_year2 = date_create("11/10/1992");
  Date* date_month1 = date_create("11/10/1991");
  Date* date_month2 = date_create("11/11/1991");
  Date* date_day1 = date_create("11/10/1991");
  Date* date_day2 = date_create("12/10/1991");
  Date* date_same1 = date_create("10/10/1991");
  Date* date_same2 = date_create("10/10/1991");
  int comp1;
  int comp2;
  int comp3;
  int comp4;
  int comp5;
  int comp6;
  int comp7;
  int comp8;
  
  comp1 = date_compare(date_year1, date_year2);
  comp2 = date_compare(date_month1, date_month2);
  comp3 = date_compare(date_day1, date_day2);
  comp4 = date_compare(date_same1, date_same2);
  comp5 = date_compare(date_month2, date_month1);
  comp6 = date_compare(date_year2, date_year1);
  comp7 = date_compare(date_day2, date_day1);
  comp8 = date_compare(date_same2, date_same1);
  
  
  
  printf("%i, %i, %i, %i, %i, %i, %i, %i", comp1, comp2, comp3, comp4, comp5, comp6, comp7, comp8);
  //printf("%i\n", all_chars(&validate_slash, 4, 8, '/', '/', '/'));
  return 0;
}

//int main(){
  //char character2;
  //char character2 = 'a';
  //  printf("%i", validate_digit(character2));
  
  //printf("%i", digest_int("19e034", 3));
  //return 0;
  /* testdate = date_create("hello"); */
  /*
  int* str = "12345";
  int* str_int = str;
  
  printf("int pointer address: %i\n", str_int);
  printf("next pointer address: %i\n", str_int + 1);
  printf("points at: %c\n", *(str_int + 1));

  char* str_char = str;
  printf("char pointer address: %i\n", str_char);
  printf("next pointer address: %i\n", str_char + 4);
  printf("points at: %c\n", *(str_char + 4));
  */
  
//}
