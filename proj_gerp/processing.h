/*
 *  processing.h
 *  Thomas Giglia
 *  4/9/2025
 *
 *
 *  COMP 15 Project 4 Gerp
 * 
 * PURPOSE: Acts as the interface for the processing functions of Gerp. This is 
 *  meant for use by an outside user with little to no programming knowledge. 
 */

#ifndef __PROCESSING_H
#define __PROCESSING_H

#include <string>
using namespace std;

string stripNonAlphaNum(string input);
void traverseDirectory(string directory);

#endif 