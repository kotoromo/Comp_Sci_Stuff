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

  printf("root: %d\n", root -> data);
  printf("Deleted data: %d\n", deleteNode(38, root));
  printf("root: %d\n", root -> data);

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
    /* In order to maintain the BST's properties, we must look for a way such
    that removing a single node would not affect these properties.

    In order to accomplish that, we must do the following:
      - We must look for a number which is smaller then the root's most-right
      child but bigger than the root (node which we want to delete).

    For that, we must make use of the BST's properties: By exploring the root's
    right branch it's obvious we will find values which are grater than that of
    the root. Then, if we want to find the smallest value in the right branch,
    we must then look at the root's right child's deepest node with a left
    child and substitute that key for the one we want to delete so that it gets
    replaced succesfully and thus enables us to delete it without worries.

    We cannot do it's left side counterpart (finding the maximum of the minimum)
    as that would disrupt the tree's balance. (NOTE: ask someone with more
    knowledge/smarter)*/

    node_t* ptr = found;

    if(ptr -> r_child -> l_child != NULL){
      while(ptr -> r_child -> l_child != NULL){
        ptr = ptr -> r_child;
        printf("[FUNCTION: deleteNode] ptr -> data: %d\n", ptr -> data);
      }

    }else{
      //Since the r_child doesn't have a left branch, then we just set the
      //r_child as the lowest maximum value.
      ptr = ptr -> r_child;
    }

      /*We traversed to the most-right node with a left child. Now we must
      traverse the most left child of the most right node's left branch.*/
    while(ptr -> l_child != NULL){
      ptr = ptr -> l_child;
    }

    /*We do the appropiate steps in order to swap the nodes.*/
    /* NOTE: Because of how I implemented the deletions, the following code
    is quite baaaaaad. I'll eventually fix this :9 */
    val = found -> data; //this is baaaaaad
    found -> data = ptr -> data;
    found = ptr;
    found -> data = val; //This aswell :S
  }

  val = found -> data;
  free(found);

  return val;
}

char* TraverseInOrder(node_t* root){
  return "a";
}
