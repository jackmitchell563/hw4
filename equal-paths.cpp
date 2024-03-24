#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool isLeaf(Node* root){
  return (not root->left and not root->right);
}


bool equalPaths(Node * root)
{
  // Add your code below
  if(!root) return true;
  // idea: if all leaves are on the same level, return true
  // in other words, if there exists a leaf on one end and a non-leaf on the other, return false
  
  if(root->left and root->right){
    if(isLeaf(root->left) and not isLeaf(root->right) or not isLeaf(root->left) and isLeaf(root->right)) return false;
    return equalPaths(root->left) and equalPaths(root->right);
  } else if(root->left){
    return equalPaths(root->left);
  } else if(root->right){
    return equalPaths(root->right);
  } else{
    return true;
  }
}

