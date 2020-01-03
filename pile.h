//
// Created by @hbFree on 1/3/2020.
//

#ifndef C_BTREES_PILE_H
#define C_BTREES_PILE_H

#include <stdio.h>
#include <stdlib.h>

typedef int pile_dtype;

// pile node struct
typedef struct pnode
{
    pile_dtype val;
    pile_dtype *next;
} pnode;

// holds head and tail
typedef struct pile
{
    pnode *head;
} pile;

// init pile
pile* pile_init();

// push val to the pile
void push(pile *p, pile_dtype val);

// pop val from the pile
pile_dtype pop(pile *p);

// return 1 if empty
int empty(pile *p);

// recursively free all pile nodes
void pile_destroy(pile *p);

#endif //C_BTREES_PILE_H
