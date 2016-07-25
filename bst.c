#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"

const int PRE_ORDER = 0;
const int IN_ORDER = 1;
const int POST_ORDER = 2;

struct bst *bst_create(void) {
  struct bst *new = malloc(sizeof(struct bst));
  new->root = NULL;
  return new;
}

// free_bstnode(t) deallocates all dynamically allocated memory 
//   within node
// effects : the memory at t is invalid (freed)
// time : O(n)
void free_bstnode (struct bstnode *node){
  if (node){
    free_bstnode(node->left);
    free_bstnode(node->right);
    free(node);
  }
}

// see interface for documentation
void bst_destroy(struct bst *t) {
  assert(t);
  free_bstnode(t->root);
  free(t);
}

// see interface for documentation
int bst_size(struct bst *t) {
  assert(t);
  return t->root->size;
}

// insert_bstnode(i,t) inserts the item i into t
// effects : mutates t to contain i, or does nothing 
//   if i is already contained in t
// time : O(h) where h is the height of the tree
struct bstnode *insert_bstnode(int i, struct bstnode *t){
  if(t == NULL){
    struct bstnode *new = malloc(sizeof(struct bstnode));
    new->item = i;
    new->left = NULL;
    new->right = NULL;
    new->size = 1;
    t = new;
  }else if (i < t->item){
    ++t->size;
    t->left = insert_bstnode(i, t->left);
  }else if (i > t->item){
    ++t->size;
    t->right = insert_bstnode(i, t->right);   
  }
  return t;
}

// see interface for documentation
void bst_insert(int i, struct bst *t) {
  assert(t);
  if(bst_find(i,t) == false){  
    t->root = insert_bstnode(i, t->root);
  }
}

// see interface for documentation
bool bst_find(int i, struct bst *t) {
  assert(t);
  struct bstnode *curnode = t->root;
  while(curnode){
    if(curnode->item == i){
      return true;
    }else if (i < curnode->item){
      curnode = curnode->left;
    }else if (i > curnode->item){
      curnode = curnode->right;
    }
  }
  return false;
}

// select_node(k,node) returns the k'th element from node in sorted order
// requires : node is not NULL and t has at least k items
// time : O(h) where h is the height of the tree
int select_node(int k, struct bstnode *node){
  assert(node && 0<=k && k<node->size);
  int left_size = 0;
  if(node->left){
    left_size = node->left->size;
  }
  if(k<left_size){
    return select_node(k, node->left);
  }else if(k == left_size){
    return node->item;
  }
  return select_node (k-left_size-1,node->right);
}

// see interface for documentation
int bst_select(int k, struct bst *t) {
  assert(t);
  return select_node(k,t->root);
}

// remove_bstnode(i,node) removes item i from node
// effects : mutates t to no longer contain i
// time : O(h) where h is the height of the tree
struct bstnode *remove_bstnode(int i, struct bstnode *node){
  if(node == NULL) return NULL;
  --node->size;
  if(i < node->item){
    node->left = remove_bstnode(i, node->left);
  }else if(i > node->item){
    node->right = remove_bstnode(i,node->right);
  }else if(node->left == NULL){
    struct bstnode *backup = node->right;
    free(node);
    return backup;
  }else if(node->right == NULL){
    struct bstnode *backup = node->left;
    free(node);
    return backup;
  }else{
    struct bstnode *next = node->right;
    while (next->left){
      next = next->left;
    }
    node->item = next->item;
    node->right = remove_bstnode(next->item, node->right);
  }
  return node;
}

// see interface for documentation
void bst_remove (int i, struct bst *t) {
  assert(t);
  if(bst_find(i,t)==true){
    t->root = remove_bstnode(i, t->root);
  }
}

// bstnode_range(start,end,t,count)mutates count to be the number of items
//   in t that are between the values of start and end (inclusive)
// time : O(n)
void bstnode_range (int start, int end, struct bstnode *t, int *count){
  if(t == NULL){
    return;
  }else if(t->item >= end){
    if(t->item == end) ++(*count);
    bstnode_range(start, end, t->left, count);
  }else if(t->item <= start){
    if(t->item == start) ++(*count);
    bstnode_range(start, end, t->right, count);
  }else{
    ++(*count);
    bstnode_range(start,end,t->right,count);
    bstnode_range(start,end,t->left,count);
  }
}
    
// see interface for documentation
int bst_range(int start, int end, struct bst *t) {
  assert(t);
  int count;
  bstnode_range(start,end,t->root,&count);
  return count;
}

// pre_print(t,beginning) print t in pre order
void pre_print(struct bstnode *t, bool beginning){
  if(t){
    if(beginning){
      printf("%d",t->item);
    }else{
      printf(",%d",t->item);
    }
    pre_print(t->left,false);
    pre_print(t->right,false);
  }
}

// in_print(t,count) print t in order
void in_print(struct bstnode *t, int *count){
  if(t){
    in_print(t->left,count);
    if(*count==1){
      printf("%d",t->item);
    }else{
      printf("%d,",t->item);
      --*count;
    }
    in_print(t->right,count);
  }
}

// post_print(t,count) print t in post order
void post_print(struct bstnode *t, int *count){
  if(t){
    post_print(t->left,count);
    post_print(t->right,count);
    if(*count==1){
      printf("%d",t->item);
    }else{
      printf("%d,",t->item);
      --*count;
    }
  }     
}

// see interface for documentation
void bst_print (int o, struct bst *t){
  assert(t);
  printf("[");
  if(o == 0){
    pre_print(t->root,true);
  }else if(o == 1 && t->root){
    int count = t->root->size;
    in_print(t->root,&count);
  }else if(o == 2 && t->root){
    int count = t->root->size;
    post_print(t->root,&count);
  }
  printf("]\n");
}

// to_array(t,arry,pos) mutates arry to contains all the item in t
//   in sorted order
// effects : mutates arry
// time : O(n)
void to_arry(struct bstnode *t, int *arry, int *pos){
  if(t){
    to_arry(t->left,arry,pos);
    arry[*pos] = t->item;
    ++*(pos);
    to_arry(t->right,arry,pos);
  }
}

// see interface for documentation
int *bst_to_sorted_array(struct bst *t) {
  assert(t);
  int *array = malloc(t->root->size*(sizeof(int)));
  int pos;
  to_arry(t->root, array, &pos);
  return array;
}

// to_bst(start,end,arr) returns a pointer to a dynamically allocated
//   node which contains all of the items from arr such that the returned 
//   bst is balanced. 
// requires : arr is sorted
// time : O(n) time
struct bstnode *to_bst(int start, int end, int*arr){
  if(start > end){
    return NULL;
  }    
  int mid = start+(end-start)/2;
  struct bstnode *new = malloc(sizeof(struct bstnode));
  new->item = arr[mid];
  new->size = end-start+1;
  new->left = to_bst(start,mid-1,arr);
  new->right = to_bst(mid+1,end,arr);
  return new;
}

// see interface for documentation
struct bst *sorted_array_to_bst(int *arr, int len) {
  assert(arr);
  struct bst *new = bst_create();
  new->root = to_bst(0,len-1,arr);
  return new;
}

// see interface for documentation
void bst_rebalance(struct bst *t) {  
  int *array = bst_to_sorted_array(t);
  struct bst *bst = sorted_array_to_bst(array,t->root->size);
  struct bstnode *backup= t->root;
  free(array);
  free_bstnode(backup);
  t->root=bst->root;
  free(bst);
}