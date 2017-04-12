#ifndef stdlib
#include <stdlib.h>
#endif

#ifndef stdio
#include <stdio.h>
#endif

typedef struct node{
    struct node* parent;
    struct node* r_child;
    struct node* l_child;
    int data;

}node_t;

typedef struct tree{
  node_t* root;
}tree_t;


typedef union data{
  int data_int;
}data_t;

char* TraverseInOrder(node_t*);
char* TraversePreOrder(node_t*);
char* TraversePostOrder(node_t*);
char* TraverseBreadthOrder(node_t*);

//void insert(node_t*, data_t*);
int insert(node_t* root, int data_int);
//void removeNode(node_t*);

node_t* createNode(data_t*);
tree_t* createTree(node_t*);

node_t* searchForNode(node_t*);
node_t* searchForData(int, node_t*);

int deleteNode(int data, node_t* root);
