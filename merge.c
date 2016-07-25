#include "merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// implementation:

void merge(struct llist *dest, struct llist *src1, struct llist *src2){
  assert(dest && src1 && src2);
  struct llnode *cur_src1 = src1->front;
  struct llnode *cur_src2 = src2->front;
  struct llnode **pos = &dest->front;
  while(cur_src1 && cur_src2){
    if(cur_src1->item < cur_src2->item){
      *pos = cur_src1;
      cur_src1 = cur_src1->next;                 
    }else{   
      *pos = cur_src2;
      cur_src2 = cur_src2->next;
    }
    pos = &((*pos)->next);
  }
  if(cur_src1){
    *pos = cur_src1;
  }else{
    *pos = cur_src2;
  }
}

void merge_sort(struct llist *lst){
  assert(lst);
  if(lst->front==NULL || lst->front->next==NULL) return;
  struct llist *left = malloc(sizeof(struct llist));
  struct llist *right = malloc(sizeof(struct llist));
  struct llnode *curnode = lst->front;
  left->front = curnode;
  right->front = curnode->next;
  struct llnode *left_pos = left->front;
  struct llnode *right_pos = right->front;
  curnode=curnode->next->next;
  int i = 0;
  while(curnode){
    if(i%2 == 0){
      left_pos->next = curnode;
      left_pos = left_pos->next;
    }else if(i%2==1){
      right_pos->next = curnode;
      right_pos = right_pos->next;
    }
    ++i;
    curnode = curnode->next;
  }
  left_pos->next = NULL;
  right_pos->next = NULL;
  merge_sort(left);
  merge_sort(right);
  merge(lst,left,right);
  free(left);
  free(right);
      
}

int main (void){
  

