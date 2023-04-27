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
    int tl_x;
    int tl_y;
    int br_x;
    int br_y;
    int hv;
}rect;

typedef struct hilbert_node{
    bool is_leaf;
    point* pnt;
    rect r;
    int num_membr;
    int lhv;
    node** children;
}node;