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



static TLDNode* create_empty_node(){
  TLDNode* empty;
  empty = (TLDNode*) malloc(sizeof(TLDNode));
  empty -> tld = NULL;
  empty -> right = NULL;
  empty -> left = NULL;
  empty -> up = NULL;
  empty -> count = 0;
  return empty;
}
static bool is_empty(TLDNode* allegedly_empty){
  return ((allegedly_empty -> tld) == NULL); 
}


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
  list_ptr -> begin = begin;
  list_ptr -> end = end;
  list_ptr -> counter = 0;
  list_ptr -> head = create_empty_node();
  return list_ptr;
}
static TLDNode* leftmost(TLDNode* node){
  while(!is_empty(node)){
    node = node->left;
  }
  return node;
}

TLDIterator *tldlist_iter_create(TLDList *tld){
  TLDIterator* returned;
  TLDNode* leftmost_node;
  returned = (TLDIterator*) malloc(sizeof(TLDIterator));
  if (!returned) return NULL;
  leftmost_node = leftmost(tld -> head);
  (returned -> tldnode_ptr) = leftmost_node;
  return returned;
}

static TLDNode* first_non_right_child(TLDNode* node_ptr){
  if (is_empty(node_ptr -> up)) return node_ptr -> up;
  elif ((node_ptr -> up -> right) == node_ptr) return first_non_right_child(node_ptr -> up);
  else return node_ptr;
}

/* returns -1 if left child, 1 if right child and 0 if head */
static int lef_or_right(TLDNode* node){
  if (is_empty(node -> up)) return 0;
  elif (node -> up -> left == node) return -1;
  else return 1;
}

TLDNode* tldlist_iter_next(TLDIterator* iter){
  TLDNode* node_ptr;
  TLDNode* go_up;
  int left_right;
  node_ptr = iter -> tldnode_ptr;
  left_right = left_or_right(node_ptr); 
  if (left_right == 0) return NULL;
  elif (left_right == -1) return node_ptr -> up;
  else
  go_up = first_non_right_child(node_ptr);
  if (is_empty(go_up)) return NULL;
  TLDNode* next = go_up -> up -> right;
  iter -> tldnode_ptr = next;
  return next;
}

static TLDNode* find_node_rec( TLDNode* node, char* tld_char ){
  int compares;
  bool is_right_empty;
  bool is_left_empty;
  compares = compare_tlds(node -> tld, tld_char);
  is_right_empty = is_empty(node -> right);
  is_left_empty = is_empty(node -> left);
  
  if (is_empty(node) || (compares == 0)) return node;
  elif (compares < 0)
     if (is_left_empty) return node -> left;
     else return find_node_rec(node -> left, tld_char);
  else
     if (is_right_empty) return node -> right;
     else return find_node_rec(node -> right, tld_char);
}

static TLDNode* find_node (TLDList* tld_list, char* tld_char){
  return find_node_rec(tld_list -> head, tld_char);
} 

static int hit_node(TLDNode* node, char* tld_char){
  if (is_empty(node)){
    (node -> right) = create_empty_node();
    (node -> left) = create_empty_node();
    node -> tld = tld_char;
    node -> count = 1;
  }
  else{
    (node -> count )++;
  }
}

int tldlist_add(TLDList* tld, char* hostname, Date* d){
  //char *tld = allo_init_tld(hostname);
  return 0;
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
  char* hostname;
  int tld;
  hostname = "adam.kurkiewicz.pl";
  tld = allo_init_tld;
  return 0;
}
