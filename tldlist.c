#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "date.h"
#include "tldlist.h"
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

int tldlist_add(TLDList* tld, char* hostname, Date* d){
  
}

int tldnode_add(TLDNode* node, char*);

static char* allo_init_tld(char* hostname){
  char* last_dot;
  for(;*hostname; hostname++){if (*hostname == '.') last_dot = hostname;}
  printf("%d,%d,%d", hostname - last_dot, hostname, last_dot);
  //malloc /* you shall free that memory when destroying */
  return last_dot; 
}
int main() {
  allo_init_tld("adam.kurkiewicz.pl"); 
  return 0;
}
