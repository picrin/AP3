#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define DATE_C_LIMIT 10
#define true 1
#define false 0
#define elif else if
typedef unsigned char siter;
typedef int iter;

struct date{
  int year;
  int month;
  int day;
};


static inline int chartoi(char number){
  return (int) number - '0';
}

static int power(int a, int b){
  int result;
  result = 1;
  while(b > 0){
    result *= a;
    b--;
  }
  return result;
}



#ifdef VALIDATE_INPUT
  static bool validate_digit(char a_char){
    char digits[DATE_C_LIMIT] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    siter i;
    bool correct;
    correct = false;
    i = 0;
    while (correct == false && i < DATE_C_LIMIT){
      if (a_char == digits[i]){
        correct = true;
      }
      i += 1;
    }
    return correct;
  }
  
  static inline bool validate_slash(char a_char){
    return (a_char == '/');
  }
  //int(*compar)(const void *, const void *)
  static bool all_chars(bool (*validator)(char), int args_num, ... ){
    va_list args;
    va_start(args, args_num);
    siter i;
    for(i = 0; i < args_num; i++){
      if (!validator(va_arg(args, int))){
        va_end(args);
        return false;
      }
    }
    va_end(args);
    return true;
  }
#endif /* VALIDATE_INPUT */

int digest_int(char* datestr_ptr, int length){
  int result;
  result = 0;
  while (length > 0){
    #ifdef VALIDATE_INPUT
    //printf("%c, %i\n", *datestr_ptr, validate_digit(*datestr_ptr));
    if (!validate_digit(*datestr_ptr)) return -1;     
    #endif /* VALIDATE_INPUT */
    result += chartoi(*datestr_ptr) * power(10, length - 1);
    length--;
    datestr_ptr++;
  }
  return result;
}

Date* date_create(char* datestr_ptr){
  Date* date_ptr;
  #ifdef VALIDATE_INPUT
  if (
      *(datestr_ptr + 10) != '\0' ||
      !all_chars(&validate_slash, 2,
          *(datestr_ptr + 2),
          *(datestr_ptr + 5)
      )
  ) return NULL;
  #endif /* VALIDATE_INPUT */
  
  date_ptr = (Date*) malloc(sizeof(Date));
  if (date_ptr == NULL) return NULL;
  date_ptr->day = digest_int(datestr_ptr, 2);
  date_ptr->month = digest_int(datestr_ptr + 3, 2);
  date_ptr->year = digest_int(datestr_ptr + 6, 4);
  return date_ptr;
}

Date* date_duplicate(Date *d){
  Date* date_ptr;
  date_ptr = (Date*) malloc(sizeof(Date));
  if (date_ptr == NULL) return NULL;
  date_ptr->day = d->day;
  date_ptr->month = d->month;
  date_ptr->year = d->year;
  return date_ptr;
}

void date_destroy(Date* d){
  free(d);
}

int date_compare(Date* date1, Date* date2){
  if (date1->year < date2->year) return -1;
  elif (date1->year > date2->year) return 1;
  else{
    if (date1->month < date2->month) return -1;
    elif (date1->month > date2->month) return 1;
    else{
      if (date1->day < date2->day) return -1;
      elif (date1->day > date2->day) return 1;
      else{
        return 0;
      }
    }
  }
}

void printdate(Date a_date){
  printf("%i/%i/%i\n", a_date.day, a_date.month, a_date.year);
}



int main(){
  Date* date1 = date_create("31/50/1991");
  printdate(*date1);
  printdate(*date_duplicate(date1));
  //printf("%i\n", all_chars(&validate_slash, 4, 8, '/', '/', '/'));
  return 0;
}
