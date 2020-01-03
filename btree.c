//
// Created by hbais on 1/3/2020.
//

#include "btree.h"

// return @ of an empty new created node
btree_node* new_btree_node()
{
    btree_node* ret = (btree_node *) malloc(sizeof(btree_node));
    ret->n_elts = 0; // no data yet
    for(int i = 0; i < BTREE_DATA_MAX + 1;++i) // no kids too
        ret->kids[i] = NULL;
    return ret;
}

// create new btree
// alloc root node & init with comparator
btree btree_init(int (*comparator) (btree_dtype, btree_dtype))
{
    btree ret;
    ret.root = new_btree_node();
    ret.comparator = comparator;
    return ret;
}

// destroy the tree
void btree_destroy(btree bt)
{
    if(bt.root == NULL)
        return;
    // destroy kids if got any (recursive)
    for(int i = 0; i < bt.root->n_elts + 1; i++) // +1 since nKids = nElts + 1
        if(bt.root->kids[i] != NULL)
        {
            btree kid_tree = {bt.root->kids[i], NULL};
            btree_destroy(kid_tree);
        }
    free(bt.root);
}


int ArrayBSearch(bs_dtype *arr, int n_elts, bs_dtype val, int *found, int (*cmp_fnc)(bs_dtype, bs_dtype))
{
    int inf = 0, sup = n_elts - 1;
    *found = 0; // not found by default
    while(inf <= sup)
    {
        int med = (inf + sup) / 2; // BSearch classic
        int cmp = cmp_fnc(val, arr[med]);
        if(cmp == 0)
        {
            *found = 1;
            return med;
        }
        if(cmp > 0) // val > middle value
            inf = med + 1;
        else
            sup = med - 1;
    }
    return inf; // the place it should be
}

// return found, node & offset
// if not found then node & offset are where the value should be stored at
btree_seek_coord btree_seek(btree_dtype val)
{
    btree_seek_coord ret = {.found = 0, .node = NULL, .pos = -1};
}