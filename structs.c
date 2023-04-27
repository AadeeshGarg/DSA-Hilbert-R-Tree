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


void pre_order_traversal(NODE node) {
    if (node == NULL) {
        return;
    }
    if (node->is_leaf){
        printf("Leaf node containing point (%d, %d)\n", node->pnt->p_x, node->pnt->p_y);
    } else {
        printf("Internal node with MBR: Top-left (%d, %d), Bottom-right (%d, %d)\n",
               node->rectangle.topleft_x, node->rectangle.topleft_y, node->rectangle.bottomright_x, node->rectangle.bottomright_y);
    }

    for (int i = 0; i < node->number_of_children; i++) {
        pre_order_traversal(node->children[i]);
    }
}


//pre_order_traversal(tree.root);