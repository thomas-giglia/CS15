/*
 *  parser.h
 *  Thomas Giglia
 *  2/18/2025
 *
 *
 *  COMP 15 Project 2 CalcYouLater
 * 
 *  PURPOSE: Acts as the interface for the parser class of linked lists 
 *  meant for use by an outside user with little to no programming knowledge. 
 */

#ifndef __PARSER_H 
#define __PARSER_H


#include <string>
#include <istream>

std::string parseRString(std::istream &input);

#endif 
