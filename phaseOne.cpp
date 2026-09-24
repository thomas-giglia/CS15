/*
 *  phaseOne.cpp
 *  Thomas Giglia
 *  4/1/2025
 *
 *
 *  COMP 15 Project 3 Zap!
 * 
 * PURPOSE: Implementation of the phaseOne functions, which help to turn text
 *          into Huffman trees and vice versa.
 */

#include "phaseOne.h"
#include <iostream>

using namespace std;


void count_freqs(istream &text) {
    int freq[256]; // Make a static array of size 256 to hold the frequencies.
    for (int i = 0; i < 256; i++) {
        freq[i] = 0; // Initialize all frequencies to 0.
    }    

    char ch;
    while (text.get(ch)) {
        // Uses the fact that characters have encoded numbers that they cast to
        // in C++ to put them in their associated slots in freq[].
        freq[ch - '\0']++; 
    }

    // Print frequencies
    for (int i = 0; i < 256; ++i) {
        // Casts the integer i back into a character and prints it.
        if (freq[i] != 0) cout << (char)(i) << ": " << freq[i] << "\n";
    }
}

std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
    std::string serialStr;  // Initialize empty string to store serialized tree

    // Base case: If the node is a leaf, serialize it as "L<char>"
    if (root->is_leaf()) {
        serialStr += "L";               // 'L' indicates a leaf node
        serialStr += root->get_val();    // Append the character stored in leaf
    } else {
        serialStr += "I";  // 'I' indicates internal node (no character stored)

        // Recursively serialize the left and right subtrees
        serialStr += serialize_tree(root->get_left());  
        serialStr += serialize_tree(root->get_right());
    }

    return serialStr;  // Return serialized string representing Huffman tree
}


HuffmanTreeNode* deserialize_helper(const std::string &s, size_t &index) {
    if (index >= s.size()) return nullptr;

    char c = s[index++];
    
    if (c == 'I') {  // Internal Node
        HuffmanTreeNode* root = new HuffmanTreeNode(nullptr, nullptr);
        root->set_left(deserialize_helper(s, index)); // Deserialize l-subtree
        root->set_right(deserialize_helper(s, index)); // Deserialize r-subtree
        return root;
    } else if (c == 'L') {  // Leaf Node
        return new HuffmanTreeNode(s[index++]); // Create a node with the char
    }
    
    return nullptr;
}

HuffmanTreeNode* deserialize_tree(const std::string &s) {
    size_t index = 0;
    return deserialize_helper(s, index);
}