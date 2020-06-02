#include <stdio.h>
#include "btree.h"

void show_node(btree_node *root)
{
    if(!root)
    {
        printf("can't show NULL node\n");
        return;
    }

    printf("[");
    for(int i = 0; i < root->n_elts; i++)
        printf("%d ", root->data[i]);
    printf("]\n");

    int i = 0;
    while(root->kids[i] && i < root->n_elts + 1)
        show_node(root->kids[i++]);
}


int main()
{
    btree bt = btree_init(comparator);
    for(int i = 0; i < 15; i++)
        btree_insert(&bt, i);
    redistribute_kids_at(bt.root, 0, REDISTRIBUTE_TO_RIGHT);
    show_node(bt.root);
    return 0;
}
