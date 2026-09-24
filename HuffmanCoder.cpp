/*
 *  HuffmanCoder.cpp
 *  Thomas Giglia
 *  4/1/2025
 *
 *
 *  COMP 15 Project 3 Zap!
 * 
 *  PURPOSE: Implementation of the HuffmanCoder class, which holds a priority
 *  queue of HuffmanTreeNode pointers and a comparator. This class provides 
 *  functionality compress files into more efficient binary strings and 
 *  uncompress them back into text files using Huffman Trees.
 */

#include "HuffmanCoder.h"

using namespace std;

/*
 * name:      HuffmanCoder (default constructor)
 * purpose:   Default constructor for HuffmanCoder class
 * arguments: None
 * returns:   None
 * effects:   Initializes an empty HuffmanCoder instance.
 */
HuffmanCoder::HuffmanCoder() {}

/*
 * name:      ~HuffmanCoder (destructor)
 * purpose:   Clean up the data in the heap from the priority queue
 * arguments: None
 * returns:   None
 * effects:   Heap memory is cleared
 */
HuffmanCoder::~HuffmanCoder() {
    // Explicitly delete every node in the heap to avoid memory leaks
    while (not pq.empty()) {
        HuffmanTreeNode* node = pq.top();
        pq.pop();
        freeTree(node); // Recursively deletes the Huffman tree nodes
    }    
}

/*
 * name:      decoder
 * purpose:   Decodes a binary file into the original text
 * arguments: Addresses of strings holding names of the input and output file
 * returns:   None
 * effects:   Writes the decoded text to the output file
 */
void HuffmanCoder::encoder(const string &inputFile, const string &outputFile) {
    // Ensures file exists before operating on it
    checkFile(inputFile);  
    ifstream input(inputFile); 

    // If file is empty, it cannot be compressed — early exit
    if (input.peek() == ifstream::traits_type::eof()) {
        cout << inputFile << " is empty and cannot be compressed.\n";
        return;
    }

    // Build the frequency map, Huffman tree, and code map to compress
    istringstream iss(count_freqs(input));
    buildTree();
    
    // Capture tree structure
    string serial = serialize_tree(pq.top());     

    // Create bit encodings for each character and string as a whole
    textMap codeMap;
    makeCodes(pq.top(), "", codeMap, '1');
    string bitString = generateBitString(codeMap, iss);

    // Save to compressed format
    writeZapFile(outputFile, serial, bitString); 
    int zapSize = bitString.length();  
    cout << "Success! Encoded given text using " << zapSize << " bits.\n";
}


/*
 * name:      decoder
 * purpose:   Decodes a binary file into the original text
 * arguments: Addresses of strings holding names of the input and output file
 * returns:   None
 * effects:   Writes the decoded text to the output file
 */
void HuffmanCoder::decoder(const string &inputFile, const string &outputFile) {
    // Ensure input file is valid
    checkFile(inputFile); 

    // Rebuild Huffman tree from serialization
    pair<string, string> input = readZapFile(inputFile); 
    HuffmanTreeNode* root = deserialize_tree(input.first);
    
    
    // Generate encoding map from deserialized tree, then invert it
    unordered_map<char,string> codeMap;
    makeCodes(root, "", codeMap, '0');
    unordered_map bitMap = invertMap(codeMap); 

    // Convert bitstring back to original text
    string output = readBits(input.second, bitMap); 

    // Save output text to file
    ofstream outFile(outputFile);
    outFile << output;

    // Clean up deserialized tree to avoid memory leaks
    freeTree(root);
}

/*
 * name:      checkFile
 * purpose:   Determines if a file exists and can be written to
 * arguments: The name of the file
 * returns:   None
 * effects:   Throws an error if the file cannot be opened.
 */
void HuffmanCoder::checkFile(string filename){
    ifstream input(filename);

    // Validates file existence before proceeding
    if (not input.is_open()) {
        throw runtime_error("Unable to open file " + filename);
    }
    
}

/*
 * name:      count_freqs
 * purpose:   Counts the frequencies of each character in the istream
 * arguments: An istream of the text from the input file
 * returns:   A string of all text in the input for reuse
 * effects:   None
 */
string HuffmanCoder::count_freqs(istream &input) {
    unordered_map<char,int> freqMap;
    char c;
    string inputStr = "";

    // Count frequency of each character to determine Huffman weights
    while (input.get(c)) {
        inputStr += c;
        freqMap[c]++;
    }

    // Build priority queue with nodes sorted by frequency
    for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
        HuffmanTreeNode* node = new HuffmanTreeNode(it->first, it->second);
        pq.push(node); // Nodes pushed into min-heap to prepare for making tree
    }

    return inputStr; 
}

/*
 * name:      makeCodes
 * purpose:   Recurses through the Huffman tree to create the Huffman codes
 * arguments: The root of the Huffman tree and reference to an unorderd map 
              (aliased as a textMap)
 * returns:   None
 * effects:   None
 */
void HuffmanCoder::makeCodes(HuffmanTreeNode* node, string path, 
                             textMap& codeMap, char bit) {
    if (not node) return;

    if (node->is_leaf()) {
        // Handle edge case for single unique char
        if (path == "") path = "0"; 
        
        // Assign Huffman code as the path
        codeMap[node->get_val()] = path; 
        return;
    }
    
    char unBit = '1';
    if (bit == '1') unBit = '0'; 

    makeCodes(node->get_left(), path + bit, codeMap, bit); // Left = 1
    makeCodes(node->get_right(), path + unBit, codeMap, bit); // Right = 0
}

/*
 * name:      freeTree
 * purpose:   Recursively delete data held in Huffman trees
 * arguments: The root node of the Huffman tree
 * returns:   None
 * effects:   Deletes all memory held by the nodes on the heap
 */
void HuffmanCoder::freeTree(HuffmanTreeNode* node) {
    if (not node) return;

    // Post-order traversal ensures children are deleted before parent
    freeTree(node->get_left());
    freeTree(node->get_right());
    
    // Free current node after its children
    delete node; 
}

/*
 * name:      serialize_tree
 * purpose:   Recurses through the Huffman tree to create a serialize string
              representing the tree.
 * arguments: Root of the tree
 * returns:   Serialized string representing the tree
 * effects:   None
 */
string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
    string serialStr = "";  

    if (root->is_leaf()) {
        // Encode leaf with marker and char value
        serialStr += "L";               
        serialStr += root->get_val();
    } else {
        // Encode internal node marker, then r-tree, then l-tree
        serialStr += "I"; 
        serialStr += serialize_tree(root->get_right()); 
        serialStr += serialize_tree(root->get_left()); 
    }

    return serialStr; 
}

/*
 * name:      buildTree
 * purpose:   Create the Huffman tree from the priority queue
 * arguments: None
 * returns:   None
 * effects:   None
 */
void HuffmanCoder::buildTree() {
    // Merge two lowest-frequency nodes until one tree remains
    while (pq.size() > 1) {
        HuffmanTreeNode* left = pq.top(); 
        pq.pop();
        HuffmanTreeNode* right = pq.top(); 
        pq.pop();

        // mergedFreq is sum of frequencies of children nodes
        int mergedFreq = left->get_freq() + right->get_freq();
        HuffmanTreeNode* internal = new HuffmanTreeNode('\0', mergedFreq);
        
        // Set left children of node as constituent nodes
        internal->set_left(left);
        internal->set_right(right);
        
        // Push merged node back into queue
        pq.push(internal); 
    }
}

/*
 * name:      generateBitString
 * purpose:   To generate a string of bits representing the text from the input
 * arguments: References to an unorderd map (aliased as a textMap) and an
              istream
 * returns:   A string of ones and zeros representing the text from the input
 * effects:   None
 */
string HuffmanCoder::generateBitString(textMap& codeMap, istream &input) {
    string bitString = "";
    char c; 

    // Replace each character from the input with its Huffman bit sequence
    while (input.get(c)) {
        // Concatenate bit encoding values associated with character keys
        bitString += codeMap[c]; 
    }

    return bitString;
}

/*
 * name:      deserialize_tree
 * purpose:   Take the serialize string for the tree and make into a tree
 * arguments: A serialized string for the tree
 * returns:   The associated Huffman tree
 * effects:   None
 */
HuffmanTreeNode* HuffmanCoder::deserialize_tree(const string &s) {
    // Recursively rebuild tree from start of serialization
    size_t index = 0; 
    return deserialize_helper(s, index);
}

/*
 * name:      deserialize_helper
 * purpose:   Take the serialize string for the tree and make into a tree 
 * arguments: A serialized string for the tree, index of where the recursion is
              is in the serial
 * returns:   The associated Huffman Tree
 * effects:   None
 */
HuffmanTreeNode* HuffmanCoder::deserialize_helper(const string &s, 
                                                  size_t &index) {
    if (index >= s.size()) return nullptr;

    char c = s[index++]; // Read current character marker

    if (c == 'I') { 
        // Match serialization order when recursing
        HuffmanTreeNode* root = new HuffmanTreeNode(nullptr, nullptr);
        root->set_left(deserialize_helper(s, index)); 
        root->set_right(deserialize_helper(s, index)); 
        return root;
    } else if (c == 'L') { 
        // Create leaf with given character
        return new HuffmanTreeNode(s[index++]); 
    }

    return nullptr;
}

/*
 * name:      invertMap
 * purpose:   To switch the order within the key value pairs of an unordered
              map holding a char and a string.
 * arguments: The address of an unorderd map (aliased as a textMap)
 * returns:   An unordered map where the elements of the pairs have their 
              orders switched. 
 * effects:   None.
 */
unordered_map<string, char> HuffmanCoder::invertMap(textMap& src) {
    unordered_map<string, char> inverted;

    // Enables reverse lookup when decoding bitstrings back to characters
    for (textMap::const_iterator it = src.begin(); it != src.end(); it++) {
        inverted[it->second] = it->first;
    }

    return inverted;
} 

/*
 * name:      readBits
 * purpose:   To use the map of key value pairs for Huffman codes and their
              associated characters to recreate the compressed message.
 * arguments: References to a string holding the string of bits and a map of
              the Huffman codes and their associated characters.
 * returns:   The recreated message.
 * effects:   None.
 */
string HuffmanCoder::readBits(string &bitString, 
                              unordered_map<string, char> &bitMap) {
    istringstream bitStream(bitString);
    char bit;
    string temp = "";
    string output = "";

    // Assembles bits one at a time until a valid Huffman code is found   
    while (bitStream.get(bit)) {
        temp += bit;

        if (bitMap.find(temp) != bitMap.end()) {
            output += bitMap[temp];
            temp = "";
        } else if (temp.length() > 32) {
            // If making unreasonably long code without finding a match, bail
            throw runtime_error("Encoding did not match Huffman tree.");
        }
    }

    // Additional check: if bits are left over that don't decode
    if (not temp.empty()) {
        throw runtime_error("Encoding did not match Huffman tree.");
    }

    return output;
}