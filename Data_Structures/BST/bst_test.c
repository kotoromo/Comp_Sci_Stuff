#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <time.h>

int main(void){
  srand(time(NULL));
  int r = rand();

  node_t* root = (node_t*) calloc(1, sizeof(node_t));
  root -> data = 50;
  root -> parent = NULL;

  printf("root_data: %d\n", root -> data);

  int arr[50];

  /*for(int i = 0; i< 50; i++){
    arr[i] = r;
  }

  for(int i = 0; i < 50; i++){
    insert(root, arr[i]);
  }*/

  //insert(root, 10022312);

  //printf("root -> l_child -> data: %d\n", root -> l_child -> data);
  /*printf("root -> r_child -> data: %d\n", root -> r_child -> data);
  printf("root -> r_child -> r_child -> l_child -> data: %d\n", root -> r_child -> l_child -> data);
  printf("root -> r_child -> l_child -> r_child ->data: %d\n", root -> r_child -> l_child -> r_child -> data);
  printf("root -> r_child -> l_child -> l_child ->data: %d\n", root -> r_child -> l_child -> l_child -> data);
  printf("root -> r_child -> l_child -> l_child -> l_child -> data: %d\n", root -> r_child -> l_child -> l_child -> l_child -> data);

  node_t* found = searchForData(10022312, root);
  if (found != NULL){
    printf("Node found with address: %p. Value: %d\n", found, found -> data);

  }*/

  insert(root, 70);
  insert(root, 60);
  insert(root, 65);
  insert(root, 80);
  insert(root, 75);
  insert(root, 85);
  printf("root -> r_child -> data: %d\n",root -> r_child -> data);
  printf("Deleted data: %d\n", deleteNode(70, root));
  printf("root -> r_child -> data: %d\n",root -> r_child -> data);

  free(root);
  return 0;
}

int insert(node_t* root, int data_int){
  if (root == NULL){
    return EXIT_FAILURE;
  }

  node_t* root_ptr = root;

  //is data_int bigger than root -> data?
  if (data_int > root_ptr -> data){
    //assign to right child....
    if (root_ptr -> r_child != NULL){
      //Has right child?
      root_ptr = root_ptr -> r_child;
      insert(root_ptr, data_int);

    }else{
      //assign node here....
      root_ptr -> r_child = (node_t*) calloc(1, sizeof(node_t));
      root_ptr -> r_child -> data = data_int;
      root_ptr -> r_child -> parent = root_ptr;
    }

  }else if (data_int < root_ptr -> data){
    //assign to left child
    if (root_ptr -> l_child != NULL){
      //Has right child?
      root_ptr = root_ptr -> l_child;
      insert(root_ptr, data_int);

    }else{
      //assign node here....
      root_ptr -> l_child = (node_t*) calloc(1, sizeof(node_t));
      root_ptr -> l_child -> data = data_int;
      root_ptr -> l_child -> parent = root_ptr;

    }

  }

  return EXIT_SUCCESS;
}

node_t* searchForData(int data, node_t* root){
  node_t* root_ptr = root;

  if (root_ptr == NULL){
    return NULL;
  }

  if(root_ptr -> data == data){
    return root_ptr;
  }

  //We perform a binary search since the tree is already sorted.

  //If the data we're looking for is smaller than the relative root's value, then
  //we search on the left.
  if(data < root_ptr -> data){
    root_ptr = root_ptr -> l_child;
    searchForData(data, root_ptr);

  }else if(data > root_ptr -> data){
    root_ptr = root_ptr -> r_child;
    searchForData(data, root_ptr);

  }
}

int deleteNode(int data, node_t* root){
  node_t* found = searchForData(data, root);

  if (found == NULL){
    return EXIT_SUCCESS;
  }

  /* Deleting a leaf node from the tree */
  if (found -> l_child == NULL && found -> r_child == NULL){

    if (found -> data > found -> parent -> data){
      found -> parent -> r_child = NULL;

    }else if(found -> data < found -> parent -> data){
      found -> parent -> l_child = NULL;

    }

    found -> parent = NULL;

  }

  /* Deleting a node with 1 child */
  if (
    (found -> l_child != NULL && found -> r_child == NULL) ||
    (found -> l_child == NULL && found -> r_child != NULL)
  ){
    node_t* child;
    //Is this node on the right or left of the parent?
    if(found -> parent -> data > found -> data){
      //It's a left child of the parent.
      if (found -> l_child != NULL){
        //if found's left child is not null...
        child = found -> l_child;
        found -> l_child = NULL;

      }else{
        //If found's right child is not null...
        child = found -> r_child;
        found -> r_child = NULL;

      }

      found -> parent -> l_child = child;
      child -> parent = found -> parent;
      found -> parent = NULL;

    }else if (found -> parent -> data < found -> data){
      //It's a right child of the parent.
      if (found -> r_child != NULL){
        //If found's right child is not NULL;
        child = found -> r_child;
        found -> r_child = NULL;
      }else{
        child = found -> l_child;
        found -> l_child = NULL;

      }

      found -> parent -> r_child = child;
      child -> parent = found -> parent;
      found -> parent = NULL;

    }

  }

  /*Deletion of a node with two children. */
  if(found -> r_child != NULL && found -> l_child != NULL){
    /*First we need to find the node which key is the next biggest one relative
    to the node we are removing.

    To remove it then, we must find a node which key is the next biggest thing
    relative to the node we are removing. We know that the bigger than root
    nodes are on the root's right side... So we just need to find the node with
    the smallest key from the node we wish to remove right branch.*/

    node_t* node_ptr = found -> r_child -> l_child;
    while(node_ptr -> l_child != NULL){
      node_ptr = node_ptr -> l_child;
      printf("[FUNCTION: deleteNode] node_ptr -> data: %d", node_ptr -> data);
    }

    node_ptr -> parent = found -> parent;
    node_ptr -> l_child = found -> l_child;
    node_ptr -> r_child = found -> r_child;

    //Find out if 'found' is is a r_child or a l_child from its parent.
    if(found -> parent -> data > found -> data){
      //It's a l_child
      found -> parent -> l_child = node_ptr;
    }else{
      //It's a r_child
      found -> parent -> r_child = node_ptr;
    }

  }

  int val = found -> data;
  free(found);

  return val;
}

char* TraverseInOrder(node_t* root){
  return "a";
}
