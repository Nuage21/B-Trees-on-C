//
// Created by hbais on 1/3/2020.
//

#ifndef C_BTREES_BTREE_H
#define C_BTREES_BTREE_H

/* simple and full B-Trees C-implementation
 * author: Hakim Beldjoudi @hbFree - JAN 2020
 */

#include <stdio.h>
#include <stdlib.h>

#define BTREE_DATA_MAX 5

// type of data used in B-Tree nodes
// compare function gotta be given later
typedef struct _btree_datatype
{
    int val;
} btree_dtype;

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
    int found; // true if strictly positive
    btree_node *node; // points to the holder if found, to the place it should be inserted if not
    int pos;
} btree_seek_coord;

// return @ of an empty new created node
btree_node* new_btree_node();

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

// return found, node & offset
// if not found then node & offset are where the value should be stored at
btree_seek_coord btree_seek(btree_dtype val);

#endif //C_BTREES_BTREE_H
