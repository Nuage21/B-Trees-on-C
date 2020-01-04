//
// Created by hbais on 1/3/2020.
//

#include "data_type.h"

int comparator(btree_dtype a, btree_dtype b)
{
    // printf("Called %d vs %d\n", a.val, b.val);
    if(a > b)
        return 1;
    if(a < b)
        return -1;
    return 0; // equality
}
