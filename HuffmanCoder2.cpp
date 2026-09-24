/*
 *  HuffmanCoder.cpp
 *  
 *  
 *
 *
 *  
 * 
 *  PURPOSE: Implementation of the phaseOne functions, which help to turn text
 *          into Huffman trees and vice versa.
 */

#include "HuffmanCoder.h"


using namespace std;

HuffmanCoder::HuffmanCoder() {}

void HuffmanCoder::encoder(const string &inputFile, const string &outputFile) {
    checkInput(inputFile);
    
    ifstream input(inputFile);
    if (input.peek() == ifstream::traits_type::eof()) {
        cout << inputFile << " is empty and cannot be compressed.\n";
        return;
    }

    // Step 1: Count frequencies
    unordered_map<char, int> freqMap = count_freqs(input);

    // Step 2: Build tree
    HuffmanTreeNode* root = buildTree(freqMap);

    // Step 3: Generate codes
    unordered_map<char, string> codeMap;
    makeCodes(root, "", codeMap);

    // Step 4: Rewind input file to re-read content
    input.clear();
    input.seekg(0);

    string bitString = generateBitString(input, codeMap);
    string serializedTree = serialize_tree(root);

    // Step 5: Write output
    writeZapFile(outputFile, serializedTree, bitString);

    cout << "Success! Encoded using " << bitString.length() << " bits.\n";
}

HuffmanTreeNode* HuffmanCoder::buildTree(unordered_map<char, int> &freqMap) {
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, 
                                    NodeComparator> pq;

    for (unordered_map<char, int>::const_iterator it = freqMap.begin(); 
                                                  it != freqMap.end(); it++) {
        char ch = it->first;
        int freq = it->second;
        pq.push(new HuffmanTreeNode(ch, freq));
    }

    while (pq.size() > 1) {
        HuffmanTreeNode* right = pq.top(); pq.pop();
        HuffmanTreeNode* left = pq.top(); pq.pop();

        HuffmanTreeNode* internal = new HuffmanTreeNode(left->get_freq() + 
                                                        right->get_freq());
        internal->set_left(left);
        internal->set_right(right);
        pq.push(internal);
    }

    return pq.top();
}

void HuffmanCoder::decoder(const string &inputFile, const string &outputFile) {
    checkInput(inputFile);
    pair<string, string> input = readZapFile(inputFile);
    HuffmanTreeNode* root = deserialize_tree(input.first);
    // printTree(root, '\0');
    unordered_map<char,string> codeMap;
    makeCodes(root, "", codeMap);
    unordered_map bitMap = invertMap(codeMap);
    string output = readBits(input.second, bitMap);
    cout << "Input = " << output << endl;

    checkOutput(outputFile);
    ofstream outFile(outputFile);
    if (outFile.is_open()) {
        outFile << output;
        outFile.close();
        cout << "Successfully written to file.\n";
    } else {
        cerr << "Failed to open the file.\n";
    }
}

string HuffmanCoder::readBits(string &bitString, 
                              unordered_map<string, char> &bitMap) {
    istringstream bitStream(bitString);
    char bit;
    string temp = "";
    string output = "";

    while(bitStream.get(bit)) {
        temp += bit;
        if (bitMap.find(temp) != bitMap.end()) {
            output += bitMap[temp];
            temp = "";
        }
    }

    return output;
    
}

string HuffmanCoder::generateBitString(unordered_map<char, string>& codeMap, 
                                       istream &input) {
    while (input.get(c)) {
        bitStream << codeMap[c];
    }
    
    return bitStream.str();
}

unordered_map<char, int> HuffmanCoder::count_freqs(istream &input) {
    unordered_map<char, int> freqMap;
    char c;
    while (input.get(c)) {
        freqMap[c]++;
    }
    return freqMap;
}

unordered_map<string, char> HuffmanCoder::invertMap(unordered_map<char, 
                                                    string>& src) {
    unordered_map<string, char> inverted;
    for (unordered_map<char, string>::const_iterator it = src.begin(); 
                                                     it != src.end(); it++) {
        inverted[it->second] = it->first;
    }

    return inverted;
} 

void HuffmanCoder::makeCodes(HuffmanTreeNode* node, string path, 
                             unordered_map<char, string>& codeMap) {
    if (not node) return;

    if (node->is_leaf()) {
        codeMap[node->get_val()] = path;
        return;
    }

    makeCodes(node->get_left(), path + "0", codeMap);
    makeCodes(node->get_right(), path + "1", codeMap);
}

string HuffmanCoder::stringToBinary(const string& input) {
    string binaryStr;
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        bitset<8> bits(c);  // 8 bits for each character
        binaryStr += bits.to_string();  // Append binary representation
    }
    return binaryStr;
}

void HuffmanCoder::print_freqs() {
    // Print frequencies
    for (int i = 0; i < 256; ++i) {
        // Casts the index integer i into a character and prints it.
        if (freq[i] != 0) cout << "[" << (char)(i) << ": " << freq[i] << "], ";
    }
    cout << endl;

}

string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
    string serialStr;  // Initialize empty string to store serialized tree

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


HuffmanTreeNode* HuffmanCoder::deserialize_helper(const string &s, 
                                                  size_t &index) {
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

HuffmanTreeNode* HuffmanCoder::deserialize_tree(const string &s) {
    size_t index = 0;
    return deserialize_helper(s, index);
}

void HuffmanCoder::checkInput(string filename){
    ifstream input(filename);
    
    if (not input.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
    input.close();    
}

void HuffmanCoder::checkOutput(string filename){
    ifstream output(filename);
    
    if (not output.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
    output.close();    
}