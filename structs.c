#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define DIMENSIONS 2

typedef struct point{
    int px;
    int py;
    int hv;
}point;

typedef struct rect{
    int tlx;
    int tly;
    int brx;
    int bry;
    int hv;
}rect;

typedef struct hilbert_node* NODE;
struct hilbert_node{
    bool isleaf;
    point* pnt;
    rect r;
    int num_membr;
    int lhv;
    NODE* children;
};


typedef struct hilbert_r_tree{
    NODE root;
    int hilbertCurveOrder;
}hilbert_r_tree;