#include "header.h"

int main(){
    TREE t;
    char str[10]="data.txt";
    t = readData(str);
    pre_order_traversal(t->root);
    return 0;
}