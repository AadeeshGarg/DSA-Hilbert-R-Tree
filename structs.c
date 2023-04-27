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

    if (node->is_leaf) {
        printf("Leaf node containing point (%d, %d)\n", node->pnt->p_x, node->pnt->p_y);
    } else {
        printf("Internal node with MBR: Top-left (%d, %d), Bottom-right (%d, %d)\n",
               node->rectangle.topleft_x, node->rectangle.topleft_y, node->rectangle.bottomright_x, node->rectangle.bottomright_y);
    }

    for (int i = 0; i < node->number_of_children; i++) {
        pre_order_traversal(node->children[i]);
    }
}











void changeFrame(int n, int *x, int *y, int quadrant) //n is sqaure size of hilbert curve
{
    switch(quadrant)
    {
        case 3:
            *x = 2*n-1 - *x;
            *y = n-1-*y;
        case 0:
            int temp = *x;
            *x = *y;
            *y = temp;
            break;
        case 2:
            *x -=n;
        case 1:
            *y -=n;
    }
}

int power(int x, int y)
{
    int ans = 1;
    for(int i = 0;i<y;i++){
        ans = ans * x;
    }
    return ans;
}

int pointToHV (int x, int y, int n) //n is order of hilbert curve
{
    int length = 0;
    int quadrant;
    for(int i = power(2, n-1);i>0;i/=2)
    {
        //printf("%d %d %d",i,x,y);
        quadrant = ((x>=i)&&(y<i))*2+(y>=i)+(x>=i);
        //printf(" %d  ", quadrant);
        length += i*i * quadrant;
        changeFrame(i,&x,&y,quadrant);
    }
    return length; 
}



bool intersect(rect r, rect q) {
    // Check if r is completely to the left of q or vice versa
    if (r.bottomright_x < q.topleft_x || q.bottomright_x < r.topleft_x) {
        return false;
    }
    
    // Check if r is completely above q or vice versa
    if (r.bottomright_y > q.topleft_y || q.bottomright_y > r.topleft_y) {
        return false;
    }
    
    // If the above two conditions are false, then r and q must overlap
    return true;
}





void Search(NODE node, rect R, int *result_set, int *count) {
    if (node == NULL) {
        return;
    }

    if (node->is_leaf) {
        // Check if the leaf node intersects the rectangle R
        if (node->pnt->p_x >= R.topleft_x && node->pnt->p_x <= R.bottomright_x && 
            node->pnt->p_y <= R.topleft_y && node->pnt->p_y >= R.bottomright_y) {
            result_set[*count] = node->pnt->hilbert_value;
            (*count)++;
        }
    } else {
        // Check if the internal node intersects the rectangle R
        if (intersect(node->rectangle,R)) {
            for (int i = 0; i < node->number_of_children; i++) {
                Search(node->children[i], R, result_set, count);
            }
        }
    }
}


