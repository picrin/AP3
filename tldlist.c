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
  //printf("%s", node);
  while(!is_empty(node->left)){
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
  (returned -> tldnode_ptr) = leftmost_node -> left;
  return returned;
}

/* returns -1 if left child, 1 if right child and 0 if head */
static int left_or_right(TLDNode* node){
  if ((node -> up) == NULL) return 0;
  elif (!is_empty(node -> up -> left) && node -> up -> left == node) return -1;
  else return 1;
}

static TLDNode* first_non_right_child(TLDNode* node_ptr){
  int is_left_or_right;
  is_left_or_right = left_or_right(node_ptr);
  if (is_left_or_right == 0) return NULL;
  elif (is_left_or_right == 1) return first_non_right_child(node_ptr -> up);
  else return node_ptr;
}

TLDNode* tldlist_iter_next(TLDIterator* iter){
  TLDNode* node_ptr;
  TLDNode* go_up;
  int left_right;
  node_ptr = iter -> tldnode_ptr;
  //TODO that's an ugly trick (below). It follows another ugly trick in return from tldlist_iter_create
  if (is_empty(node_ptr)) return iter -> tldnode_ptr = node_ptr -> up;
  left_right = left_or_right(node_ptr);
  if (!is_empty(node_ptr -> right)){
    //printf("mozna w prawo\n");
    return iter -> tldnode_ptr = leftmost(node_ptr -> right);
  }
  elif (left_right == -1){ 
    //printf("nie moge w prawo, ale jestem lewy\n");
    return iter -> tldnode_ptr = node_ptr -> up;
  }
  else{
    //printf("nie moge w prawo i jestem prawy\n");
    go_up = first_non_right_child(node_ptr);
      //printf("first_non_right %s", go_up -> tld);
      if (go_up == NULL) return NULL;
      else{
        TLDNode* next = go_up -> up;
        return iter -> tldnode_ptr = next;
      }
  }
}
static char* allo_init_tld(char* hostname){
  char* last_dot;
  char* new_mem;
  int i;
  for(;*hostname; hostname++){if (*hostname == '.') last_dot = hostname;}
  //printf("%d, %d, %d", hostname - last_dot, hostname, last_dot);
  //printf("%c, %c, %c, %i, %i, %i", *last_dot, *(last_dot + 1), *(last_dot + 2), *(last_dot + 3), *hostname, *(hostname + 1));
  new_mem = (char*) malloc(sizeof(char) * (hostname - last_dot)); /* you shall free that memory when destroying  */
  for(i = 0, last_dot++; *last_dot; last_dot++, i++){ *(new_mem + i) = *last_dot;}
  return new_mem;
}

static TLDNode* find_node_rec( TLDNode* node, char* tld_char ){
  int compares;
  bool is_right_empty;
  bool is_left_empty;
  if (is_empty(node)) return node;
  compares = compare_tlds(tld_char, node -> tld);
  is_right_empty = is_empty(node -> right);
  is_left_empty = is_empty(node -> left);  
  if (compares == 0) return node;
  elif (compares < 0){
     //printf("%s < %s\n", tld_char, node -> tld);
     if (is_left_empty) return node -> left;
     else return find_node_rec(node -> left, tld_char);
  } else {
     //printf("%s > %s\n", tld_char, node -> tld);
     if (is_right_empty) return node -> right;
     else return find_node_rec(node -> right, tld_char);
  }
}

static TLDNode* find_node (TLDList* tld_list, char* tld_char){
  return find_node_rec(tld_list -> head, tld_char);
} 

static int hit_node(TLDNode* node, char* tld_char){
  /* this potentially deallocs memory from init_alloc */
  if (is_empty(node)){
    (node -> right) = create_empty_node();
    (node -> right -> up) = node;
    (node -> left) = create_empty_node();
    (node -> left -> up) = node;
    node -> tld = tld_char;
    node -> count = 1;
  }
  else{
    (node -> count )++;
    free(tld_char);
  }
  return node -> count;
}
int tldlist_add(TLDList* tld, char* hostname, Date* d){
  char* tld_char;
  //printf("%s", "bad data\n");

  if (date_compare(d, tld -> begin) < 0 || date_compare(tld-> end, d) < 0)
    {/*printf("%s", "nie ja\n");*/ return 0; }
  else {
    //printf("%s", "nie ty\n");
    (tld -> counter) ++;
    TLDNode* correct_node;
    tld_char = allo_init_tld(hostname);
    correct_node = find_node(tld, tld_char);
    hit_node(correct_node, tld_char);
    return 1;
  }
}

/*static void indent(char* appendto, int indentation_level){
  int i;
  for (i = 0; i < 2*indentation_level; i++) strcat(appendto, " ");
} */

/*static void unsafe_inorder_rec(TLDNode* node, char* appendtto, int indentation_level){
  if (is_empty(node)){
    strcat(appendtto, "(N)");
    return;
  } else {
    strcat(appendtto, "(");
    unsafe_inorder_rec(node -> left, appendtto, indentation_level + 2);
    strcat(appendtto, node -> tld);
    unsafe_inorder_rec(node -> right, appendtto, indentation_level + 2);
    strcat(appendtto, ")");
    return;
  }
}*/

/*static char* unsafe_inorder(TLDNode* node){
  char* totalchar = malloc(sizeof(char)*4096); //unsafe, this might be too small
  strcat(totalchar,"#inorder");
  unsafe_inorder_rec(node, totalchar, 2); 
  return totalchar;
}*/

char* tldnode_tldname(TLDNode *node){
  return node -> tld;
}

long tldlist_count(TLDList *tld){
  //printf("%d", tld -> counter);
  return tld -> counter;
}

void tldlist_destroy(TLDList *tld){
  free(tld);
}

long tldnode_count(TLDNode *node){
  //printf("%d", node -> count);
  return node -> count;
}

void tldlist_iter_destroy(TLDIterator *tld){
  free(tld);
}
