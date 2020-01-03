//
// Created by @hbFree on 1/3/2020.
//

#include "pile.h"

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