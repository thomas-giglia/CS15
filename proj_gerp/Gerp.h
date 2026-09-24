/*
 *  RPNCalc.cpp
 *  Thomas Giglia
 *  2/27/2025
 *
 *
 *  COMP 15 Project 2 CalcYouLater
 * 
 * 
 *  PURPOSE: Acts as the interface for the RPNCalc program and the users inputs 
 *  meant for use by an outside user with little to no programming knowledge. 
 */

#ifndef __GERP_H 
#define __GERP_H
  
  
#include <string>
#include <iostream>
  
class Gerp {
  public:
    Gerp();
    void run();
    int gerpHash(std::string word); 
  private:
    //list of file_paths[file's lines<file's words>];
    int filled_buckets;
    int total_buckets = 1000;
    double max_load_factor;   
    std::vector<std::vector<std::vector<std::string>>> hash;
    std::vector<std::vector<std::vector<std::string>>> iHash;
     
}; 

#endif 