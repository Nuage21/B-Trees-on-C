#include <stdio.h>
#include "btree.h"

int main()
{
    // test insertion
    btree bt = btree_init(comparator);

    for(int i = 0; i < BTREE_DATA_MAX + 1; i++)
    {
        btree_dtype v = {.val = i * 2};
        btree_insert(&bt, v);
        printf("%d inserted\n", i * 2);
    }

    btree_dtype v = {.val = 1};
    btree_insert(&bt, v);

    v.val = 3;
    btree_insert(&bt, v);

    v.val = 5;
    btree_insert(&bt, v);

    for(int i = 0; i < bt.root->n_elts; i++)
        printf("%d ", bt.root->data[i]);

    return 0;
}
