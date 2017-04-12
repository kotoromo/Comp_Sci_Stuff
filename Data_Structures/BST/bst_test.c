#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <time.h>

int main(void){
  srand(time(NULL));
  int r = rand();

  int arr[9] = {5, 1, 9, 8, 15, 13, 45, 47, 46};

  /*for(int i = 0; i< 50; i++){
    arr[i] = r;
  }*/
  node_t* root = (node_t*) calloc(1, sizeof(node_t));
  root -> data = 38;

  for(int i = 0; i < 9; i++){
    insert(root, arr[i]);
  }

  //printf("root: %d\n", root -> data);
  printf("Deleted data: %d\n", deleteNode(38, root));
  printf("root: %d\n", root -> data);
  /*printf("root -> r_child -> data: %d\n", root -> r_child -> data);

  printf("Deleted data: %d\n", deleteNode(45, root));
*/
  TraverseInOrder(root);

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
    /* Else, we search on the right */
    root_ptr = root_ptr -> r_child;
    searchForData(data, root_ptr);

  }
}

int deleteNode(int data, node_t* root){
  int val = 0;
  node_t* found = searchForData(data, root);

  if (found -> l_child != NULL && found -> r_child != NULL){
    node_t* ptr = found -> l_child;

    while(ptr -> r_child != NULL){
      ptr = ptr -> r_child;
    }

    found -> data = ptr -> data;
    deleteNode(ptr -> data, ptr);

  }else if(found -> l_child != NULL || found -> r_child != NULL){
    node_t* ptr = found;

    //is found an r_child or l_child?
    if (found -> data > found -> parent -> data){
      //Found node is an r_child
      if(found -> l_child != NULL){
        found -> parent -> r_child = found -> l_child;
      }else{
        found -> parent -> r_child = found -> r_child;
      }
    }else{
      //FOund node is an l_child:
      if(found -> r_child != NULL){
        found -> parent -> l_child = found -> l_child;
      }else{
        found -> parent -> l_child = found -> r_child;
      }

    }

    free(found);

  }else if(found -> l_child == NULL && found -> r_child == NULL){
    //is found an r_child or l_child?
    if (found -> parent -> data > found -> data){
      //found is an l_child
      found -> parent -> l_child = NULL;

    }else{
      //found is an r_child.
      found -> parent -> r_child = NULL;
    }

    free(found);
  }

  return val;
}

char* TraverseInOrder(node_t* root){
  if(root == NULL){
    return "a";
  }
  node_t* ptr = root;
  TraverseInOrder(ptr -> l_child);
  printf("-> %d", ptr -> data);
  TraverseInOrder(ptr -> r_child);

  //NOTE: For some reason it still prints out the deleted value... :/

  return "a";
}
