#include "sequence.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// implementation:
struct Sequence {
  struct node *front;
};

struct node{
  int item;
  struct node *next;
};

struct Sequence *Sequence_create(void){
  struct Sequence *new = malloc(sizeof(struct Sequence));
  new->front = NULL;
  return new;
}

void Sequence_destroy(struct Sequence *seq){
  assert(seq);
  struct node *curnode = seq->front;
  while (curnode){
    struct node *next_node = curnode->next;
    free(curnode);
    curnode = next_node;
  }
  free(seq);
}

int Sequence_length(const struct Sequence *seq){
  assert(seq);
  int count=0;
  struct node *curnode = seq->front;
  while(curnode){
    ++count;
    curnode=curnode->next;
  }
  return count;
}

int Sequence_item_at(const struct Sequence *seq, int pos){
  assert(seq);
  assert(pos>=0 && pos<Sequence_length(seq));
  struct node *curnode = seq->front;
  while(pos > 0){
    curnode = curnode->next;
    --pos;
  }
  return curnode->item;
}

void Sequence_insert_at(struct Sequence *seq, int pos, int val){
  assert(seq);
  assert(pos>=0 && pos<=Sequence_length(seq));
  struct node *new = malloc (sizeof(struct node));
  new->item = val;
  if(pos == 0){
    new->next = seq->front;
    seq->front = new;
  }else{
    struct node *curnode = seq->front;
    while (pos > 1){
      curnode = curnode->next;
      --pos;
    }
    new->next = curnode->next;
    curnode->next = new;
  }
}

int Sequence_remove_at(struct Sequence *seq, int pos){
  if (pos == 0){
    assert(seq);
    assert(pos>=0 && pos<Sequence_length(seq));
    struct node *temp = seq->front;
    int val = seq->front->item;
    seq->front=seq->front->next;
    free(temp);
    return val;
  }else{
    struct node *curnode = seq->front;
    while (pos > 1){
      curnode = curnode->next;
      --pos;
    }
    struct node *temp = curnode->next;
    int val = curnode->next->item;
    curnode->next =curnode->next->next;
    free(temp);
    return val;
  }
}

void Sequence_print(const struct Sequence *seq){
  assert(seq);
  struct node *curnode = seq->front;
  int len = Sequence_length(seq);
  printf("[%d]",len);
  while(curnode){
    printf(" %d",curnode->item);
    curnode = curnode->next;
  }
  printf("\n");
}
    
  