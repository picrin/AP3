#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "date.h"
#include "tldlist.h"
#define elif else if
/*
int main(){
  //char* buffer = (char*) malloc(sizeof(char)*10);
  char buffer[10];
  char* result = fgets(buffer, 10, stdin);
  if (result != NULL)
    printf("%s, %lu", buffer, sizeof(buffer));
  else printf("NULL");
  return 0;
}
*/


struct tldlist{
  TLDNode* head;
  Date* begin;
  Date* end;
  int counter;
};

struct tldnode{
  char* tld;
  TLDNode* left;
  TLDNode* right;
  TLDNode* up;
  int count;
};

struct tlditerator{
  TLDNode* tldnode_ptr;
};

static inline int compare_tlds(char* tldA, char* tldB){
  return strcmp(tldA, tldB);
}

TLDList* tldlist_create(Date *begin, Date *end){
  TLDList* list_ptr;
  
  list_ptr = (TLDList*) malloc(sizeof(TLDList));
  if (!list_ptr) return NULL;
  list_ptr -> begin = NULL;
  list_ptr -> end = NULL;
  return list_ptr;
}

TLDIterator *tldlist_iter_create(TLDList *tld){
  TLDNode* current_leftmost;
  TLDIterator* returned;
  current_leftmost = tld->head;
  while(current_leftmost != NULL){
    current_leftmost = current_leftmost->left;
  }
  returned = (TLDIterator*) malloc(sizeof(TLDIterator));
  if (!returned) return NULL;
  returned -> tldnode_ptr = current_leftmost;
  return returned;
}

static TLDNode* first_non_right_child(TLDNode* node_ptr){
  if ((node_ptr -> up) == NULL) return NULL;
  if ((node_ptr -> up -> right) == node_ptr) return first_non_right_child(node_ptr -> up);
  else return node_ptr;
}

TLDNode* tldlist_iter_next(TLDIterator* iter){
  TLDNode* node_ptr;
  TLDNode* go_up;
  node_ptr = iter -> tldnode_ptr;
  if ((node_ptr -> right) != NULL) return node_ptr -> right;
  go_up = first_non_right_child(node_ptr);
  if (go_up == NULL) return NULL;
  TLDNode* next = go_up -> up -> right;
  iter -> tldnode_ptr = next;
  return next;
}

static TLDNode* find_neighbourhood( TLDList* tld_list, char* tld_char){
  if (tld -> head ==  NULL) return NULL;
  else return find_neighbourhood_rec(tld_list -> head, tld_char);
} 

static TLDNode* find_neighbourhood_rec( TLDNode* node, char* tld_char ){
  int compares;
  bool is_rightNULL;
  bool is_leftNULL;
  compares = compare_tlds(node -> tld, tld_char);
  is_rightNULL = (node -> right == NULL);
  is_leftNULL = (node -> left == NULL);
  if (is_leftNULL && is_rightNULL)
    || (compare == 0)
    || (is_rightNULL && compare > 0)
    || (is_leftNULL && compare < 0)
    return node;
  elif (compare > 0)
    return  find_neighbourhood_rec( node -> right, tld_char);  
  elif (compare < 0)
    return  find_neighbourhood_rec( node -> left, tld_char);
}

static TLDNode* finish_off_neighbourhood

int tldlist_add(TLDList* tld, char* hostname, Date* d){
 char *tld = allo_init_tld(hostname);
 
}

int tldnode_add(TLDNode* node, char*);

static char* allo_init_tld(char* hostname){
  char* last_dot;
  char* new_mem;
  int i;
  for(;*hostname; hostname++){if (*hostname == '.') last_dot = hostname;}
  //printf("%d, %d, %d", hostname - last_dot, hostname, last_dot);
  //printf("%c, %c, %c, %i, %i, %i", *last_dot, *(last_dot + 1), *(last_dot + 2), *(last_dot + 3), *hostname, *(hostname + 1));
  new_mem = (char*) malloc(sizeof(char) * (hostname - last_dot)); /* you shall free that memory when destroying  */
  for(i = 0, last_dot++; *last_dot; last_dot++, i++){ *(new_mem + i) = *last_dot;}
    *(new_mem + i) = '\0';
  return new_mem;
}
int main() {
  char* fuckyou;
  fuckyou = allo_init_tld("adam.kurkiewicz.pl");
  printf("%s, adflsdjfh", fuckyou);
  free(fuckyou);
  return 0;
}
