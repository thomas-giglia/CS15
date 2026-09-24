#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <queue>
#include <vector>
#include <unordered_map>
#include <bitset>

#include <iostream>
#include <sstream>
#include <fstream>

#include "HuffmanTreeNode.h"
#include "ZapUtil.h"
#include "phaseOne.h"

class HuffmanCoder {
  public:
    HuffmanCoder();
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);

  private:
    void checkInput(std::string filename);
    void checkOutput(std::string filename);
    void checkEmpty(std::string filename);

    void print_freqs();
    std::unordered_map<char, std::string> count_freqs(std::istream &text);
    std::string serialize_tree(HuffmanTreeNode *root);
    HuffmanTreeNode *deserialize_tree(const std::string &s);
    HuffmanTreeNode *deserialize_helper(const std::string &s, 
                                        size_t &index);
    
    HuffmanTreeNode* HuffmanCoder::buildTree(unordered_map<char, int> &freq_map)
    void makeCodes(HuffmanTreeNode *root, std::string code,
                   std::unordered_map<char, std::string> &codes);
    std::string generateBitString(std::unordered_map<char, std::string> &codes, 
                                  std::istream &input);

    std::unordered_map<std::string, char> invertMap(
        std::unordered_map<char, std::string> &src);
    std::string readBits(std::string &bits, std::unordered_map<std::string, 
                                                               char> &bit_map);
    std::string stringToBinary(const std::string &input);

};

#endif