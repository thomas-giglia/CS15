/*
 *  unit_test.h
 *  Thomas Giglia
 *  4/1/2025
 *
 *  COMP 15 Project 3 Zap!
 *  
 *  PURPOSE: Tested various parts of the phaseOne functions that work to turn
 *           text into Huffman trees and vice versa, now just tests error
 *           throwing for nonexistent files
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include "HuffmanCoder.h"

using namespace std;


// Test1: only test remaining, here to make sure nonexistent files through the
// correct error messages
void testFileErrorCatching() {
    bool exceptionThrown = false;
    string expectedMessage = "Encoding did not match Huffman tree.";
        
    try {
        HuffmanCoder coder;
        coder.decoder("bad_zap_file", "output.zap");
    } catch (const runtime_error &e) {
        exceptionThrown = true;
        // Optional: Check if message is exactly or partially as expected
        assert(string(e.what()).find(expectedMessage) != string::npos);
    }

    assert(exceptionThrown && "Expected std::runtime_error was not thrown");
}

