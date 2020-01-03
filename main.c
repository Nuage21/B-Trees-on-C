#include <stdio.h>
#include "btree.h"

int comparator(btree_dtype a, btree_dtype b)
{
    printf("Called %d vs %d\n", a.val, b.val);
    if(a.val > b.val)
        return 1;
    if(a.val < b.val)
        return -1;
    return 0; // equality
}

int main() {

    return 0;
}
