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
    for(int i = 0; i < bt.root->kids[0]->n_elts; i++)
        printf("%d ", bt.root->kids[0]->data[i]);

    return 0;
}
