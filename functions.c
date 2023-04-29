#include "header.h"

TREE createNewTree(){
    TREE t = (TREE)malloc(sizeof(struct hilbert_r_tree));
    t->root = NULL;
    t->hilbert_curve_order = CurveOrder;
}

NODE createNewLeaf(point* p){
    NODE n = (NODE)malloc(sizeof(struct hilbert_node));
    n->is_leaf = true;
    n->children = (NODE*)calloc(M+1,sizeof(NODE));
    n->largest_hilbert_value = p->hilbert_value;
    n->number_of_children = 0;
    n->parent = NULL;
    n->pnt = p;
    n->rectangle.topleft_x = p->p_x;
    n->rectangle.bottomright_x = p->p_x;
    n->rectangle.topleft_y = p->p_y;
    n->rectangle.bottomright_y = p->p_y;
}

NODE createNewNode(){
    NODE n = (NODE)malloc(sizeof(struct hilbert_node));
    n->is_leaf = false;
    n->children = (NODE*)calloc(M+1,sizeof(NODE));
    n->largest_hilbert_value = 0;
    n->number_of_children = 0;
    n->parent = NULL;
    n->pnt = NULL;
}

void pre_order_traversal(NODE node) {
    if (node == NULL) {
        printf("Tree is empty.");
        return;
    }

    if (node->is_leaf) {
        printf("Leaf node containing point (%d, %d)\n", node->pnt->p_x, node->pnt->p_y);
    } else {
        printf("Internal node with MBR: Top-left (%d, %d), Bottom-right (%d, %d)\n",
               node->rectangle.topleft_x, node->rectangle.topleft_y, node->rectangle.bottomright_x, node->rectangle.bottomright_y);
    }
    if(node->is_leaf){
        return;
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

int pointToHV (int x, int y, int n) //n is order of hilbert curve
{
    int length = 0;
    int quadrant;
    for(int i = pow(2, n-1);i>0;i/=2)
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

void Search(NODE node, rect R, point **result_set, int *count) {
    // result set should be dynamically alloted memory
    if (node == NULL) {
        return;
    }
    if (node->is_leaf) {
        // Check if the leaf node lies inside/on the rectangle R
        if (node->pnt->p_x >= R.topleft_x && node->pnt->p_x <= R.bottomright_x && 
            node->pnt->p_y <= R.topleft_y && node->pnt->p_y >= R.bottomright_y) {
            // put point in result set
            if((*count)==(sizeof(result_set)/sizeof(point*))){
                result_set = realloc(result_set,2*(*count)*(sizeof(point*)));
            }
            *(result_set + *count) = node->pnt;
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

void adjust_node(NODE node){
    if (node == NULL) {
        return;
    }
    if (node->is_leaf) {
        return;
    }
    if(node->number_of_children==0){
        return;
    }

    // if children are leaf nodes
    if(node->children[0]->is_leaf){
        for(int i=0;i<node->number_of_children;i++){
            //update largest_hilbert_value
            if (node->children[i]->pnt->hilbert_value > node->largest_hilbert_value){
                node->largest_hilbert_value = node->children[i]->pnt->hilbert_value;
            }
            //update rectangle
            if( node->children[i]->pnt->p_x > node->rectangle.bottomright_x){
                node->rectangle.bottomright_x  =  node->children[i]->pnt->p_x; 
            }
            if( node->children[i]->pnt->p_x < node->rectangle.topleft_x){
                node->rectangle.topleft_x  =  node->children[i]->pnt->p_x; 
            }
            if( node->children[i]->pnt->p_y > node->rectangle.topleft_y){
                node->rectangle.topleft_y  =  node->children[i]->pnt->p_y; 
            }
            if( node->children[i]->pnt->p_y < node->rectangle.bottomright_y){
                node->rectangle.bottomright_y  =  node->children[i]->pnt->p_y; 
            }
        }
    }
    // if children are not leaf nodes
    else{
        for(int i=0;i<node->number_of_children;i++){
            //update largest_hilbert_value
            if (node->children[i]->largest_hilbert_value > node->largest_hilbert_value){
                node->largest_hilbert_value = node->children[i]->largest_hilbert_value;
            }

            //update rectangle
            if( node->children[i]->rectangle.topleft_x < node->rectangle.topleft_x){
                node->rectangle.topleft_x  =  node->children[i]->rectangle.topleft_x; 
            }
            if( node->children[i]->rectangle.topleft_y > node->rectangle.topleft_y){
                node->rectangle.topleft_y  =  node->children[i]->rectangle.topleft_y; 
            }
            if( node->children[i]->rectangle.bottomright_x > node->rectangle.bottomright_x){
                node->rectangle.bottomright_x  =  node->children[i]->rectangle.bottomright_x; 
            }
            if( node->children[i]->rectangle.bottomright_y < node->rectangle.bottomright_y){
                node->rectangle.bottomright_y  =  node->children[i]->rectangle.bottomright_y; 
            }

        }
    }
    
}

NODE chooseLeaf(NODE node, point* p){
    if(node->children == NULL){
        return node;
    }
    else if(node->children[0]->is_leaf){
        return node;
    }
    else{
        int i = 0;
        for(; i < node->number_of_children;i++){
            if(p->hilbert_value > node->children[i]->largest_hilbert_value){
                continue;
            }
            else{
                break;
            }
        }
        return chooseLeaf(node->children[i],p);
    }
}

void insertIntoNode(NODE parent, NODE child){
    child->parent = parent;
    int i = 0;
    for(;i<parent->number_of_children;i++){
        if(child->largest_hilbert_value > parent->children[i]->largest_hilbert_value){
            continue;
        }
        else{
            break;
        }
    }
    int j = i;
    NODE prev = parent->children[i];
    for(;i<parent->number_of_children;i++){
        NODE temp = parent->children[i+1];
        parent->children[i+1]=prev;
        prev = temp;
    }
    parent->children[j] = child;
    parent->number_of_children++;
}

NODE* secondGenList(NODE grandParent, int noOfChildren)
{
    int cnt = 0;
    NODE* nodelist = (NODE*)malloc((noOfChildren)*sizeof(NODE));
    for(int i = 0;i<grandParent->number_of_children;i++)
    {
        for(int j =0;j<grandParent->children[i]->number_of_children;j++)
        {
            nodelist[cnt] = grandParent->children[i]->children[j];
            cnt++;
        }
    }
    return nodelist;
}

int splitCount(int eleCount, int nodeCount)
{
    while (eleCount>=nodeCount)
        eleCount -= nodeCount;
    return eleCount;
    
}

void balanceTree(NODE parent, int sum)
{
    NODE* nodelist = secondGenList(parent, sum);
        int counter = 0;
        int splitcnt = splitCount(sum, parent->number_of_children);
        int i;
        for(i = 0;i<parent->number_of_children;i++)
        {
            for(int j =0;j<parent->children[i]->number_of_children;j++)
            {
                parent->children[i]->children[j]=NULL;
            }
            parent->children[i]->number_of_children =0;
        }
        for(i = 0; i<splitcnt; i++)
        {
            for(int j =0; j<=1+(sum/parent->number_of_children);j++)
                insertIntoNode(parent->children[i], nodelist[counter]);
        }
        for(; i<parent->number_of_children; i++)
        {
            for(int j =0; j<=(sum/parent->number_of_children);j++)
                insertIntoNode(parent->children[i], nodelist[counter]);
        }
        free(nodelist);
}

void handleOverflow(NODE toInsert, TREE rTree)
{
    bool createdNewNode = false;
    int sum = 0;
    NODE parent = toInsert->parent;
    if(parent!=NULL)
    {
        for(int i = 0; i<parent->number_of_children;i++)
        {
            sum+=parent->children[i]->number_of_children;
        }
        if(sum<=M*parent->number_of_children)
        {
            balanceTree(parent, sum);
        }
        else
        {
            insertIntoNode(parent, createNewNode());
            balanceTree(parent, sum);
            createdNewNode = true;
        }
        for(int i = 0; i < parent->number_of_children; i++){
            adjust_node(parent->children[i]);
        }
    }
    else
    {
        parent = createNewNode();
        insertIntoNode(parent, toInsert);
        handleOverflow(toInsert, rTree);
        if(parent->number_of_children =1)
        {
            free(parent);
            toInsert->parent = NULL;
        }
        else
        {
            rTree->root = parent;
        }
    }

}

TREE insertNewPointinTREE(TREE t, point* p){
    NODE n = chooseLeaf(t->root,p);
    insertIntoNode(n,createNewLeaf(p));
    while(n->number_of_children == 5){
        handleOverflow(n,t);
        if(n->parent==NULL){
            break;
        }
        n = n->parent;
    }
    while(n!=NULL){
        adjust_node(n);
        n = n->parent;
    }
    return t;
}

TREE readData(char*str12){
    TREE t;
    t = createNewTree();
    FILE* fp;
    fp = fopen(str12,"r");
    int x,y;
    while(fscanf(fp, "%d %d", &x, &y) != EOF){
        point* p = (point*)malloc(sizeof(point));
        p->p_x = x;
        p->p_y = y;
        p->hilbert_value = pointToHV(x,y,CurveOrder);
        //insertNewPointinTREE(t,p);
    }
    fclose(fp);
    return t;
};
