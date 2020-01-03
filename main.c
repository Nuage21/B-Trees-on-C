#include <stdio.h>
#include "btree.h"
#include "pile.h"

int comparator(btree_dtype a, btree_dtype b)
{
    // printf("Called %d vs %d\n", a.val, b.val);
    if(a.val > b.val)
        return 1;
    if(a.val < b.val)
        return -1;
    return 0; // equality
}

int main() {

    pile *p = pile_init();
    push(p, 23);
    push(p, 2);
    push(p, 5);

    while(!empty(p)) // while not empty
        printf("%d ", pop(p));

    pile_destroy(p);
    return 0;
}
