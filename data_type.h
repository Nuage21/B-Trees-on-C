//
// Created by hbais on 1/3/2020.
//

#ifndef C_BTREES_DATA_TYPE_H
#define C_BTREES_DATA_TYPE_H

// type of data used in B-Tree nodes
// compare function gotta be given later
typedef int btree_dtype;


// provide order relation
int comparator(btree_dtype a, btree_dtype b);

#endif //C_BTREES_DATA_TYPE_H
