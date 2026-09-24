/*
 *  phaseOne.h
 *  Thomas Giglia
 *  4/1/2025
 *
 *
 *  COMP 15 Project 3 Zap!
 * 
 * PURPOSE: Acts as the interface for the phaseOne functions of Zap! which is 
 *  meant for use by an outside user with little to no programming knowledge. 
 */

#ifndef __PHASEONE_H
#define __PHASEONE_H

#include <istream>
#include <string>
#include "HuffmanTreeNode.h"

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(const std::string &s);
HuffmanTreeNode* deserialize_helper(const std::string &s, size_t &index);

#endif