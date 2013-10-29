#include "tldlist.h"
#include "date.h"
#include <stdbool.h>
#include <stdlib.h>


int main() {
  char* hostname;
  int tld;
  TLDIterator* myiter;
  TLDNode* pointat;
  Date* dummydate, *left_date, *right_date;
  TLDNode *node, *node_left, *node_right, *node_ll, *node_lr;
  TLDList* mylist;
  //printf("%s", "|");
  left_date = date_create("10/10/1900");
  right_date = date_create("10/10/2100");
  dummydate = date_create("11/10/1991");
  //printf("%d", strcmp("c", "d"));
  //return strcmp(tldA, tldB);
  //printf("%d",strcmp("hello", "a(c = getchar()) != EOF)ello"));
  mylist = tldlist_create(left_date, right_date);
  tldlist_add(mylist, "www.intel.com", dummydate);
  //tldlist_add(mylist, ".2", dummydate);
  //tldlist_add(mylist, "www.dcs.gla.ac.uk", dummydate);
  //tldlist_add(mylist, "www.mit.edu", dummydate);
  //tldlist_add(mylist, "www.cms.rgu.ac.uk", dummydate);
  tldlist_add(mylist, ".f", dummydate);
  tldlist_add(mylist, ".j", dummydate);
  tldlist_add(mylist, ".n", dummydate);
  tldlist_add(mylist, ".a", dummydate);

  tldlist_add(mylist, ".a", dummydate);
  //tldlist_add(mylist, ".o", dummydate);
  //tldlist_add(mylist, ".e", dummydate);
  //tldlist_add(mylist, ".c", dummydate);
  //tldlist_add(mylist, ".c", dummydate);
  //tldlist_add(mylist, ".c", dummydate);
  //tldlist_add(mylist, ".g", dummydate);
  //tldlist_add(mylist, ".i", dummydate);
  //tldlist_add(mylist, ".k", dummydate);
  //tldlist_add(mylist, ".m", dummydate);
  //tldlist_add(mylist, ".o", dummydate);
  //printf("%s", unsafe_inorder(mylist -> head));
  //myiter =  tldlist_iter_create(mylist);
  //printf("%s", myiter -> tldnode_ptr -> up -> tld);
  //printf("%s", "nima");
  //if (pointat != NULL) printf("huja");
  //printf("%s", myiter -> tldnode_ptr -> tld);
  /*pointat = tldlist_iter_next(myiter);
  while (pointat != NULL){
    printf("%s%d", tldnode_tldname(pointat), tldnode_count(pointat)); 
    pointat = tldlist_iter_next(myiter);
  }*/
  
  return 0;
}
