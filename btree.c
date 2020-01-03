//
// Created by @hbFree on 1/3/2020.
//

#include "btree.h"


pile* pile_init()
{
    pile *p = (pile *) malloc(sizeof(pile));
    p->head = NULL;
    return p;
}


// insert at beginning
void push(pile *p, pile_dtype val)
{
    pnode *node = (pnode*) malloc(sizeof(pnode));
    node->val = val;
    node->next = p->head;
    p->head = node;
}


// gotta check if empty before
pile_dtype pop(pile *p)
{
    if(p->head) //  check not empty
    {
        pile_dtype ret = p->head->val;
        pnode *tmp = p->head;
        p->head = p->head->next;
        free(tmp);
        return ret;
    }
}

int empty(pile *p)
{
    if(!p->head)
        return 1; // empty
    return 0;
}

void pile_destroy(pile *p)
{
    pnode *node = p->head;
    while(node)
    {
        pnode *nxt = node->next;
        free(node);
        node = nxt;
    }
    p->head = NULL; // just in case used even after freed
    free(p);
}


// return @ of an empty new created node
btree_node* btree_new_node()
{
    btree_node* ret = (btree_node *) malloc(sizeof(btree_node));
    ret->n_elts = 0; // no data yet
    for(int i = 0; i < BTREE_DATA_MAX + 1;++i) // no kids too
        ret->kids[i] = NULL;
    return ret;
}

// new btree with NULL root
// init with comparator
btree btree_init(int (*comparator) (btree_dtype, btree_dtype))
{
    btree ret;
    ret.root = NULL;
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
btree_seek_coord btree_seek(btree bt, btree_dtype val, int _addPile, pile *p)
{
    btree_seek_coord ret = {.node = NULL, .pos = -1};
    if(bt.root == NULL || bt.comparator == NULL)
        return ret; // invalid (shall be provided with valid node and comparator)
    int found = -1;
    ret.node = bt.root; // update last accessed node
    int shd_be_placed = ArrayBSearch(bt.root->data, bt.root->n_elts, val, &found, bt.comparator);

    if(found > 0) // found = true
    {
        ret.node = bt.root;
        ret.pos = shd_be_placed;
        return ret;
    }
    // if doesn't have a kid there
    if(bt.root->kids[shd_be_placed] == NULL)
        return ret;
    // if has then seek at
    btree kid_btree = {.root = bt.root->kids[shd_be_placed], .comparator = bt.comparator};

    if(_addPile > 0)
        push(p, bt.root);

    return btree_seek(kid_btree, val, _addPile, p);
}

// insert val to the b-tree bt
// return 1 if success
// 0 if an error occurs
// -1 if value already in tree
int btree_insert(btree *bt, btree_dtype val)
{
    if(bt->comparator == NULL)
        return 0; // btree not initiated
    if(bt->root == NULL)
    {
        bt->root = btree_new_node();
        bt->root->data[0] = val;
        bt->root->n_elts = 1;
        return 1; // success
    }

    pile *p = pile_init(); // will contains the ascendants of the node which it should be in
    btree_seek_coord sk = btree_seek(*bt, val, 1, p); // first of all search if it exists

    if(sk.pos >= 0) // found ?
        return -1; // value already inserted

    btree_node *right = NULL;
    while(sk.node != NULL)
    {
        if(sk.node->n_elts < BTREE_DATA_MAX) // last accessed node has room for ?
        {
            int i = sk.node->n_elts - 1;
            for(; i >= 0; --i)
            {
                // move elements right till right place found
                if(bt->comparator(sk.node->data[i], val) < 0)
                    break;
                sk.node->data[i+1] = sk.node->data[i]; // move right
                sk.node->kids[i+1] = sk.node->kids[i]; // move kids
            }
            sk.node->data[i+1] = val; // place node
            sk.node->kids[i+2] = right; // place right node
            sk.node->n_elts++;
            return 1; // success
        }
        // if there's no room for then...

        // alloc holder array
        int array_len =  1 + sk.node->n_elts;
        btree_dtype *seq = (btree_dtype *) malloc(sizeof(btree_dtype) * array_len);

        int inserted = 0; // val isn't yet inserted in the array
        for(int i = 0; i < array_len - 1; )
        {
            btree_dtype tmp = sk.node->data[i];
            if(inserted > 0 || bt->comparator(val, tmp) > 0) // if inserted or val > tmp
            {
                seq[i + inserted] = tmp;
                ++i;
            }
            else
            {
                seq[i] = val;
                sk.node->kids[i + 1] = right; // insert right node
                inserted = 1;
            }
        }
        if(!inserted)
            seq[sk.node->n_elts] = val; // if not inserted then it shall be on the extreme right


        // now split into two nodes
        int nElts = sk.node->n_elts;
        int middle_index = (nElts + 1) / 2;
        btree_dtype middle_val = sk.node->data[middle_index];

        // store left half into original node (left node)
        sk.node->n_elts = middle_index;
        memmove(sk.node->data, seq, middle_index);

        // create the right node
        btree_node *right_node = btree_new_node();
        memmove(right_node->data, seq + middle_index + 1, sizeof(btree_dtype) * (nElts - middle_index)); // copy data
        memmove(right_node->kids, sk.node->kids + middle_index + 1, sizeof(btree_dtype) * (nElts - middle_index)); // copy kids
        right_node->n_elts = nElts - middle_index;

        memset(sk.node->kids + middle_index, 0, nElts - middle_index); // nullify left node's rightest kids

        // if has no parent
        if(empty(p))
        {
            btree_node *parent = btree_new_node();
            parent->n_elts = 1; // holds the middle value only
            parent->data[0] = middle_val;
            parent->kids[0] = sk.node; // left child
            parent->kids[1] = right_node; // left child
            bt->root = parent; // new root
            return 1; // success
        }

        right = right_node;
        // if has parent
        sk.node = pop(p);
        free(seq);
    }
    pile_destroy(p);
    return 1;
}