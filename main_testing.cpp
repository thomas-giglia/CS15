
/*
 *  phaseOne.cpp
 *  Thomas Giglia
 *  4/1/2025
 *
 *
 *  COMP 15 Project 3 Zap!
 * 
 * PURPOSE: Acts as a way to easily test that small inputs work correctly and 
 *  to check that the program compiles as it should.
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// string capturePreorderTraversal(HuffmanTreeNode* root);

int main() {

    
}

// // Function to print the tree in preorder (for verification)
// string capturePreorderTraversal(HuffmanTreeNode* root) {
//     ostringstream output;
//     if (!root) return "";

//     if (root->get_left() == nullptr && root->get_right() == nullptr) { // Leaf
//         output << "L" << root->get_val();
//     } else { // Internal node
//         output << "I";
//     }

//     output << capturePreorderTraversal(root->get_left());
//     output << capturePreorderTraversal(root->get_right());

//     return output.str();
// }