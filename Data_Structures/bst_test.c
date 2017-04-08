#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(void){
  node_t* root = (node_t*) calloc(1, sizeof(node_t));
  root -> data = 2;
  root -> parent = NULL;

  printf("root_data: %d\n", root -> data);

  int arr[5] = {43, 22, 23, 12, 9};

  for(int i = 0; i < 5; i++){
    insert(root, arr[i]);
  }

  //printf("root -> l_child -> data: %d\n", root -> l_child -> data);
  printf("root -> r_child -> data: %d\n", root -> r_child -> data);
  printf("root -> r_child -> r_child -> l_child -> data: %d\n", root -> r_child -> l_child -> data);
  printf("root -> r_child -> l_child -> r_child ->data: %d\n", root -> r_child -> l_child -> r_child -> data);
  printf("root -> r_child -> l_child -> l_child ->data: %d\n", root -> r_child -> l_child -> l_child -> data);
  printf("root -> r_child -> l_child -> l_child -> l_child -> data: %d\n", root -> r_child -> l_child -> l_child -> l_child -> data);



  free(root);
  return 0;
}

int insert(node_t* root, int data_int){
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

    }

  }

  return EXIT_SUCCESS;
}

char* TraverseInOrder(node_t* root){
  return "a";
}
