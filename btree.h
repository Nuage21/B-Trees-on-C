//
// Created by @hbFree on 1/3/2020.
//

#ifndef C_BTREES_BTREE_H
#define C_BTREES_BTREE_H

/* simple and full B-Trees C-implementation
 * author: Hakim Beldjoudi @hbFree - JAN 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_type.h"

#define BTREE_DATA_MAX 5

// node struct
typedef struct btree_node {
    btree_dtype data[BTREE_DATA_MAX];
    struct btree_node* kids[BTREE_DATA_MAX + 1];
    size_t n_elts;
} btree_node;


// tree holder
typedef struct btree
{
    btree_node *root;
    int (*comparator) (btree_dtype, btree_dtype);
} btree;

// when btree_seek called
typedef struct btree_seek_coord
{
    btree_node *node; // points to the holder if found, to the place it should be inserted if not
    int pos; // found if >= 0
} btree_seek_coord;


// pile node struct
typedef btree_node* pile_dtype;
typedef struct pnode
{
    pile_dtype val;
    struct pnode *next;
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


// return @ of an empty new created node
btree_node* btree_new_node();


// create new btree
// alloc root node & init with comparator
btree btree_init(int (*comparator) (btree_dtype, btree_dtype));


// destroy the tree
void btree_destroy(btree bt);


// found or not stored @found
// return: position if found
//      -> the position it should (the kid that would hold it) if not found
typedef btree_dtype bs_dtype; // specify data_type for search function
int ArrayBSearch(bs_dtype *arr, int n_elts, bs_dtype val, int *found, int (*cmp_fnc)(bs_dtype, bs_dtype));


// return 1 if node is a leaf (doesn't have kids) - 0 if internal node
int is_leaf(btree_node *node);


#define REDISTRIBUTE_TO_RIGHT 1
#define REDISTRIBUTE_TO_LEFT -1
// gotta verify before if the two nodes at pos exist
void redistribute_kids_at(btree_node *node, int pos, int sense);


// return found, node & offset
// if not found then node & offset are where the value should be stored at
btree_seek_coord btree_seek(btree bt, btree_dtype val, int _addPile, pile *p);


// insert val to the b-tree bt
// return: 1 for success - 0 if an error occurs - -1 if the value already exist in the b-tree
int btree_insert(btree *bt, btree_dtype val);

// delete val from the b-tree bt
// return: 1 for success - 0 if an error occurs - -1 if the value already doesn't exist in the b-tree
int btree_delete(btree *bt, btree_dtype val);

#endif //C_BTREES_BTREE_H
