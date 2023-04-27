#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define DIMENSIONS 2
#define m 2
#define M 4

typedef struct point{
    int p_x;
    int p_y;
    int hilbert_value;
}point;

typedef struct rect{
    int topleft_x;
    int topleft_y;
    int bottomright_x;
    int bottomright_y;
    int hilbert_value;
}rect;

typedef struct hilbert_node* NODE;
struct hilbert_node{
    bool is_leaf;
    point* pnt;
    rect rectangle;
    int number_of_children;
    int largest_hilbert_value;
    NODE* children;
};


typedef struct hilbert_r_tree{
    NODE root;
    int hilbert_curve_order;
}hilbert_r_tree;


