/*
 *  unit_test.h
 *  Thomas Giglia
 *  4/1/2025
 *
 *  COMP 15 Project 3 Zap!
 *  
 *  PURPOSE: Tests various parts of the phaseOne functions that work to turn
 *           text into Huffman trees and vice versa
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include "HuffmanCoder.h"

using namespace std;

// Helper function to capture the output of count_freqs()
string captureOutput(istream &input) {
    ostringstream output;
    streambuf* oldCout = cout.rdbuf(output.rdbuf()); // Redirect cout to output
    count_freqs(input);
    cout.rdbuf(oldCout);  // Restore cout
    return output.str();
}

// Test 1: Count frequencies in a simple string
void testSimpleString() {
    istringstream input("hello");
    string result = captureOutput(input);
    assert(result.find("h: 1") != string::npos);
    assert(result.find("e: 1") != string::npos);
    assert(result.find("l: 2") != string::npos);
    assert(result.find("o: 1") != string::npos);
}

// Test 2: Check frequency of spaces and punctuation
void testSpacesAndPunctuation() {
    istringstream input("hello, world!");
    string result = captureOutput(input);
    assert(result.find("h: 1") != string::npos);
    assert(result.find("e: 1") != string::npos);
    assert(result.find("l: 3") != string::npos);
    assert(result.find("o: 2") != string::npos);
    assert(result.find(",: 1") != string::npos);
    assert(result.find(" : 1") != string::npos);
    assert(result.find("!: 1") != string::npos);
}

// Test 3: Check case sensitivity
void testCaseSensitivity() {
    istringstream input("HelloHELLO");
    string result = captureOutput(input);
    assert(result.find("H: 2") != string::npos);
    assert(result.find("e: 1") != string::npos);
    assert(result.find("E: 1") != string::npos);
    assert(result.find("l: 2") != string::npos);
    assert(result.find("L: 2") != string::npos);
    assert(result.find("o: 1") != string::npos);
    assert(result.find("O: 1") != string::npos);
}

// Test 4: Handle empty input
void testEmptyInput() {
    istringstream input("");
    string result = captureOutput(input);
    assert(result.empty());  // No characters, so no output
}

// Test 5: Handle repeated characters
void testRepeatedCharacters() {
    istringstream input("aaaabbbb");
    string result = captureOutput(input);
    assert(result.find("a: 4") != string::npos);
    assert(result.find("b: 4") != string::npos);
}
// Test 6: Serialize a simple tree with one internal node and two leaf nodes
void testSerializeSimpleTree() {
    HuffmanTreeNode* leftChild = new HuffmanTreeNode('D');
    HuffmanTreeNode* rightChild = new HuffmanTreeNode('E');
    HuffmanTreeNode* root = new HuffmanTreeNode(leftChild, rightChild);
    string result = serialize_tree(root);
    assert(result == "ILALB");  // Expected format
}

// Test 7: Serialize a single leaf node (edge case)
void testSerializeSingleLeaf() {
    HuffmanTreeNode* root = new HuffmanTreeNode('C');
    string result = serialize_tree(root);
    assert(result == "LC");
}

// Test 8: Serialize a deeper tree structure
void testSerializeDeepTree() {
    HuffmanTreeNode* leftChild = new HuffmanTreeNode('D');
    HuffmanTreeNode* rightChild = new HuffmanTreeNode('E');
    HuffmanTreeNode* parent = new HuffmanTreeNode(leftChild, rightChild);
    HuffmanTreeNode* root = new HuffmanTreeNode(parent, 
                                                new HuffmanTreeNode('F'));

    string result = serialize_tree(root);
    assert(result == "IILDLILELF");  // Pre-order traversal serialization
}

// Test 9: Serialize a tree with only internal nodes (invalid case)
void testSerializeOnlyInternalNodes() {
    HuffmanTreeNode* root = new HuffmanTreeNode(new HuffmanTreeNode(nullptr, 
                                                          nullptr), nullptr);
    string result = serialize_tree(root);
    assert(result.find("I") == 0);  // Must start with "I" since internal node
}

// Test 10: Serialize a complex tree with mixed internal and leaf nodes
void testSerializeComplexTree() {
    HuffmanTreeNode* left = new HuffmanTreeNode(new HuffmanTreeNode('X'), 
                                                new HuffmanTreeNode('Y'));
    HuffmanTreeNode* right = new HuffmanTreeNode('Z');
    HuffmanTreeNode* root = new HuffmanTreeNode(left, right);

    string result = serialize_tree(root);
    assert(result == "IILLXLYLZ");  // Expected serialized output
}

// Function to print the tree in preorder (for verification)
string capturePreorderTraversal(HuffmanTreeNode* root) {
    ostringstream output;
    if (!root) return "";

    if (root->get_left() == nullptr && root->get_right() == nullptr) { // Leaf
        output << "L" << root->get_val() << " ";
    } else { // Internal node
        output << "I ";
    }

    output << capturePreorderTraversal(root->get_left());
    output << capturePreorderTraversal(root->get_right());

    return output.str();
}

// Test 1: Simple tree with one internal node and two leaves
void testSimpleTree() {
    string serialized = "ILaLb";
    HuffmanTreeNode* root = deserialize_tree(serialized);
    
    string result = capturePreorderTraversal(root);
    assert(result == "ILaLb");
}

// Test 2: Single leaf node (edge case)
void testSingleLeaf() {
    string serialized = "La";  // A single leaf node with 'a'
    HuffmanTreeNode* root = deserialize_tree(serialized);
    
    string result = capturePreorderTraversal(root);
    assert(result == "La");
}

// Test 3: Deeply nested tree (checks recursion depth)
void testDeeplyNestedTree() {
    string serialized = "IILaLbLc";
    HuffmanTreeNode* root = deserialize_tree(serialized);

    string result = capturePreorderTraversal(root);
    assert(result == "IILaLbLc");
}

// Test 4: Empty input (edge case)
void testEmptyDeserializationInput() {
    string serialized = "";
    HuffmanTreeNode* root = deserialize_tree(serialized);

    string result = capturePreorderTraversal(root);
    assert(result.empty());  // Should be empty since there's no tree
}

// Test 5: Complex tree with mixed structure
void testComplexTree() {
    string serialized = "IILaILbLcLd";
    HuffmanTreeNode* root = deserialize_tree(serialized);

    string result = capturePreorderTraversal(root);
    assert(result == "IILaILbLcLd");
}
