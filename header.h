#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#define DIMENSIONS 2
#define m 2
#define M 4
#define CurveOrder 8

typedef struct hilbert_node* NODE;
typedef struct hilbert_r_tree* TREE;
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
}rect;
struct hilbert_node{
    NODE parent;
    bool is_leaf;
    point* pnt;
    rect rectangle;
    int number_of_children;
    int largest_hilbert_value;
    NODE* children;
};
struct hilbert_r_tree{
    NODE root;
    int hilbert_curve_order;
};

TREE createNewTree();
NODE createNewLeaf(point*);
NODE createNewNode();

void pre_order_traversal(NODE);
void changeFrame(int, int*, int*, int); 
int pointToHV (int , int , int ); 
bool intersect(rect , rect ); 
void Search(NODE , rect , point**, int*);
void adjust_node(NODE); 
NODE chooseLeaf(NODE , point* );
void insertIntoNode(NODE , NODE );
NODE* secondGenList(NODE, int);
int splitCount(int, int );
void balanceTree(NODE, int );
void handleOverflow(NODE, TREE );
TREE insertNewPointinTREE(TREE, point*);
TREE readData(char*);

