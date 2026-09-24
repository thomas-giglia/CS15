/*
 *  HuffmanCoder.h
 *  Thomas Giglia
 *  4/1/2025
 *
 *
 *  COMP 15 Project 3 Zap!
 * 
 *  PURPOSE: Acts as the interface for the HuffmanCoder class for user inputs
 *  meant for use by an outside user with little to no programming knowledge. 
 */

#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include "HuffmanTreeNode.h"
#include "ZapUtil.h"

using namespace std;

typedef unordered_map<char, string> textMap;


class HuffmanCoder {
  public:
    HuffmanCoder();
    ~HuffmanCoder();
    void encoder(const string &inputFile, const string &outputFile);
    void decoder(const string &inputFile, const string &outputFile);

  private:
    // general helper functions
    void checkFile(string filename);
    string count_freqs(istream &text);
    void makeCodes(HuffmanTreeNode *root, string code, textMap &codes, char c);
    void freeTree(HuffmanTreeNode* node);

    // encoder helper functions
    string serialize_tree(HuffmanTreeNode *root);
    void buildTree();
    string generateBitString(textMap &codes, istream &input);

    // decoder helper functions
    HuffmanTreeNode *deserialize_tree(const string &s);
    HuffmanTreeNode *deserialize_helper(const string &s, size_t &index);
    unordered_map<string, char> invertMap(textMap &src);
    string readBits(string &bits, unordered_map<string, char> &bit_map);

    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, 
                                     NodeComparator> pq;
};

#endif