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
static int left_or_right(TLDNode* node){
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
static TLDNode* find_node_rec( TLDNode* node, char* tld_char ){
  int compares;
  bool is_right_empty;
  bool is_left_empty;
  compares = compare_tlds(node -> tld, tld_char);
  if (is_empty(node)) return node;
  is_right_empty = is_empty(node -> right);
  is_left_empty = is_empty(node -> left);
  
  if (compares == 0) return node;
  elif (compares < 0){
     printf("%s < %s\n", tld_char, node -> tld);
     if (is_left_empty) return node -> left;
     else return find_node_rec(node -> left, tld_char);
  } else {
     printf("%s > %s\n", tld_char, node -> tld);
     if (is_right_empty) return node -> right;
     else return find_node_rec(node -> right, tld_char);
  }
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
  return node -> count;
}

int tldlist_add(TLDList* tld, char* hostname, Date* d){
  char* tld_char;
  TLDNode* correct_node;
  tld_char = allo_init_tld(hostname);
  correct_node = find_node(tld, tld_char);
  hit_node(correct_node, tld_char);
  return correct_node -> count;
}

static void indent(char* appendto, int indentation_level){
  int i;
  for (i = 0; i < 2*indentation_level; i++) strcat(appendto, " ");
} 

void unsafe_yaml_rec(TLDNode* node, char* appendtto, int indentation_level){
  indent(appendtto, indentation_level);
  strcat(appendtto, "- node:\n");
  indent(appendtto, indentation_level + 1);  
  if (is_empty(node)){
    strcat(appendtto, "tld: ");
    strcat(appendtto, "empty\n");
    return;
  } else {
    strcat(appendtto, "tld: ");
    strcat(appendtto, node -> tld);
    strcat(appendtto, "\n");
    indent(appendtto, indentation_level + 1);
    strcat(appendtto, "nodes:\n");
    unsafe_yaml_rec(node -> left, appendtto, indentation_level + 2);
    unsafe_yaml_rec(node -> right, appendtto, indentation_level + 2);
    return;
  }
}
void unsafe_inorder_rec(TLDNode* node, char* appendtto, int indentation_level){
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
}
char* unsafe_yaml(TLDNode* node){
  char* totalchar = malloc(sizeof(char)*4096); //unsafe, this might be too small
  strcat(totalchar,"#YAML 1.2\nbinary tree:\n  head:\n");
  unsafe_yaml_rec(node, totalchar, 2); 
  return totalchar;
}

char* unsafe_inorder(TLDNode* node){
  char* totalchar = malloc(sizeof(char)*4096); //unsafe, this might be too small
  strcat(totalchar,"#inorder");
  unsafe_inorder_rec(node, totalchar, 2); 
  return totalchar;
}

int main() {
  char* hostname;
  int tld;
  Date* dummydate;
  TLDNode *node, *node_left, *node_right, *node_ll, *node_lr;
  TLDList* mylist;
  dummydate = date_create("11/10/1991");
  hostname = "adam.kurkiewicz.pl";
  node = create_empty_node();
  node_left = create_empty_node();
  node_ll = create_empty_node();
  node_lr = create_empty_node();
  node_right = create_empty_node();
  node -> left = node_left;
  node -> left -> tld = "1";
  node -> left -> left = node_ll;
  node -> left -> right = node_lr;
  node -> right = node_right;
  node -> tld = "2";
  printf("%d", strcmp("a", "c"));
  //return strcmp(tldA, tldB);
  //printf("%d",strcmp("hello", "aello"));
  mylist = tldlist_create(dummydate, dummydate);
  /*tldlist_add(mylist, ".a", dummydate);
  tldlist_add(mylist, ".b", dummydate);
  tldlist_add(mylist, ".c", dummydate);
  tldlist_add(mylist, ".d", dummydate);
  tldlist_add(mylist, ".e", dummydate);
  tldlist_add(mylist, ".f", dummydate);
  printf("%s", unsafe_inorder(mylist -> head));
  */
  return 0;
}
