/*
 *  RPNCalc.cpp
 *  Thomas Giglia
 *  2/27/2025
 *
 *
 *  COMP 15 Project 2 CalcYouLater
 * 
 * 
 *  PURPOSE: Implementation of the RPNCalc class, which holds a stack of datum
 *  objects. This class provides functionality to perform various arithmetic, 
 *  boolean, and organizaitonal commands on the data within the stack.
 */

#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include "RPNCalc.h"
#include <vector>

using namespace std;

/*
 * name:      RPNCalc
 * purpose:   Default constructor for RPNCalc
 * arguments: none
 * returns:   none
 * effects:   Initializes an empty RPNCalc instance.
 */
RPNCalc::RPNCalc() {
    cont = true;
}

/*
 * Name:        run
 * Purpose:     Takes user inputs and performs proper operations on them using 
 *              the other functions
 * Parameters:  None
 * Returns:     None
 * Effects:     Manages stack operations
 */
void RPNCalc::run() {
    pushPrep(cin);
}

/*
 * Name:        read
 * Purpose:     To find datum objects to push from an rstring
 * Parameters:  An parsed rstring
 * Returns:     A string to push to the stack
 * Effects:     Splits inputs into constiuent parts
 */
string RPNCalc::read(string temp) {
    int nestLvl = 0;
    string input = "";
    int length = temp.length();
    
    for (int i = 0; i < length; i++) {
        
        // If whitespace is found outside of an rstring, treat it as a
        // delimiter and push the content found, then reset the input string
        if ((temp[i] == ' ' or temp[i] == '\n') and nestLvl == 0) {
            push(input);
            input = "";

        // If Track any braces found and change nestLvl accordingly
        } else if (temp[i] == '{') {
            nestLvl++;
            if (nestLvl > 0) input += '{';
        } else if (temp[i] == '}') {
            nestLvl--;
            input += '}';
        
        // Add any other characters to the input string
        } else{
            input += temp[i];
        }
    }

    return input;
}

/*  Name:       parse
 *  Purpose:    To parse values for the program into rstrings to be 
 *              interpreted.
 *  Parameters: the input that needs to be parsed into an rstring.
 *  Return:     None
 *  Effects:    None
 */
 string RPNCalc::parse(istream &input) {    
    int nestLvl = 1; 
    string inputString, temp; 
    string rstring = "{ ";
    
    // While input still has content to read, read it in
    while (input >> inputString) { 
        // Add spaces only if not acting as unnecessary whitespace
        if (inputString.length() > 0 and inputString[0] != ' ') {
            temp += " ";
        }

        // Add all other content from the string in
        temp += inputString;

        // Change nestLvl if braces are found
        if (inputString == "{") { 
            nestLvl++;
        } else if (inputString == "}") {
            nestLvl--;
        
        // Exit function if last brace necessary is found
        } else if (nestLvl <= 0) {
            return temp;
        }
    }  

    return temp;
 }

/*
 * Name:        push
 * Purpose:     To add datum objects to the stack
 * Parameters:  An rstring representing the datum's value
 * Returns:     None
 * Effects:     Adds the datum to the stack
 */
void RPNCalc::push(string datumVal) {
    // Temporary variables to make got_int work
    int tempNumber = 7;
    int* potInt = &tempNumber;
    
    // If quit is found, end the operation
    if (datumVal == "quit") {
        cont = false; 
        return;

    // If the datumVal has no content, ignore it
    } else if (datumVal.length() == 0) {
        return;
    
    // Search for integers, boolean, or rstrings and push them to stack
    } else if (got_int(datumVal, potInt)){
        stack.push(Datum(*potInt));
    }else if (datumVal[0] == '#') {
        convertBool(datumVal);
    } else if (datumVal[0] == '{') {
        stack.push(Datum(datumVal));
    
    // If none of those are found, check if it's an implemented command
    } else {
        findCommand(datumVal);
    }
}

/*
 * Name:        checkForCommands
 * Purpose:     Finds valid commands in inputs and runs them
 * Parameters:  The input from the user
 * Returns:     A string to push to the stack
 * Effects:     Outputs error if the command is unimplemented
 */
 void RPNCalc::findCommand(string cmd) {
    // Many conditionals to try to find command
    if (cmd == "+" or cmd == "-" or cmd == "*" or cmd == "/" or cmd == "mod") {
        doMath(cmd);
    } else if (cmd == "<" or cmd == ">" or cmd == "<=" or cmd == ">=") {
        relate(cmd);
    } else if (cmd == "==") {
        equate();
    } else if (cmd == "not") {
        stackNot();
    } else if (cmd == "print") {
        print();
    } else if (cmd == "swap" or cmd == "drop" or cmd == "dup") {
        stackChange(cmd);
    } else if  (cmd == "clear") {
        stack.clear();
    } else if (cmd == "exec") {
        exec();
    } else if (cmd == "if") {
        stackIf();
    } else if (cmd == "file") {
        file();
    } else if (cmd == "quit" or cmd == "qui") {
        cont = false;
    } else if (cmd[0] == '#') {
        convertBool(cmd);
    
    // If command is not found, cerr that information
    } else { 
        cerr << cmd << ": unimplemented\n";
    }
}

/*
 * Name:        print
 * Purpose:     Prints out the top item on the stack to std::cout followed by a
 *              new line
 * Parameters:  None
 * Returns:     None
 * Effects:     None (doesn't pop off first element, just reads and outputs it)
 */
void RPNCalc::print() const {
    // Check that stack has itemps to print
    if (stack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    
    // Check if datum is an integer, and if so print that value
    } else if (stack.top().isInt()) {
        cout << stack.top().getInt() << endl;
    
    // Check if datum is an boolean, and if so print that value as #t or #f
    } else if (stack.top().isBool()) {
        if (stack.top().getBool()) {
            cout << "#t" << endl;
        } else {
            cout << "#f" << endl;
        }
    
    // Check if datum is an rstring, and if so print that value
    } else if (stack.top().isRString()) {
        cout << stack.top().getRString() << endl;
    }
}

/*
 * Name:        exec
 * Purpose:     Executes the commands that are stored in rstrings of the class
 *              based on the information within them and on the stack.
 * Parameters:  None
 * Returns:     None
 * Effects:     Pops off a datum and executes it if possible
 */
void RPNCalc::exec() {
    try {
        // Attempt to pop value from the stack
        Datum executable = stack.pop();  

        // Check that the executable is an rstring
        if (executable.isRString()) {
            // Remove extra braces and spaces from executable
            string rstring = executable.getRString();
            rstring = rstring.substr(2, rstring.length() - 3);
            rstring = read(rstring);
            
            push(rstring);
        } else {
            // Throw an error if it is not
            throw runtime_error("Error: cannot execute non rstring\n");     
        }

    // Catch any errors thrown by stack.pop and/or exec and cerr them
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    }
}

/*
 * Name:        file
 * Purpose:     To open a file at the top of the stack if possible
 * Parameters:  None
 * Returns:     None
 * Effects:     Creates an istringstream of the information in the file to read
 *              data in from 
 */
void RPNCalc::file() {
    try {
        // Attempt to pop value from the stack
        Datum fileRString = stack.pop(); 

        // Output to cerr if not properly formatted
        if (not fileRString.isRString()) {
            cerr << "Error: file operand not rstring\n"; 
            return;
        }

        // Remove braces from file name and make into ifstream pointer on heap
        string filename = fileRString.getRString();
        filename = filename.substr(2, filename.length() - 4);
        ifstream *fileStream = new ifstream(filename);  

        // Determine if given file is valid, if not cerr that and delete it
        if (not fileStream->is_open()) {
            cerr << "Unable to read " << filename << endl;
        } else {
            inputStack.push_front(fileStream); 
            pushPrep(*fileStream);  // Push file stream onto input stack
        }

        // Delete the pointer to clean up
        delete fileStream;

    // Catch any errors that stack.pop may have thrown and cerr them
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    }
}

/*
 * Name:        pushPrep
 * Purpose:     Reads in any commands from an istringstream and adds them to 
 *              the stack.
 * Parameters:  None
 * Returns:     None
 * Effects:     Add any data from the istringstrem to the stack. 
 */
void RPNCalc::pushPrep(istream &fileStream) {
    inputStack.push_front(&fileStream);  // Push new input source
    string temp;
    
    while (not inputStack.empty() and cont) {
        istream *currentStream = inputStack.front();
        
        if (not (*currentStream >> temp)) {  // If EOF reached
            inputStack.pop_front();  // Remove the current stream
            if (inputStack.empty()) {  
                cont = false;  // Only quit if no more input sources
            }
            continue;
        }

        if (temp == "{") {
            temp = "{" + parse(*currentStream);
        }
        push(read(temp));
    }
}

/*
 * Name:        stackIf
 * Purpose:     To execute conditional statements created from the first three
 *              items on the stack.
 * Parameters:  None
 * Returns:     None
 * Effects:     Throws an error if the stack doesn't have enough elements or
 *              they are not formatted properly for the command.
 */
void RPNCalc::stackIf() {
    try {
        // Attempt to pop two values from the stack
        Datum resultFalse = stack.pop();  
        Datum resultTrue = stack.pop();  
        Datum conditional = stack.pop();  

        // Throw errors if poorly formatted
        if (not resultFalse.isRString()) {
            throw runtime_error("Error: expected rstring in if branch");   
        }
        if (not resultTrue.isRString()) {
            throw runtime_error("Error: expected rstring in if branch");   
        }
        if (not conditional.isBool()) {
            throw runtime_error("Error: expected boolean in if test");   
        }

        // Perform the boolean operation
        if (conditional.getBool()) {
            push(resultTrue.getRString());
        } else {
            push(resultFalse.getRString());
        }
        exec();
    
    // Catch any errors that stack.pop() may have throwm and cerr them    
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    }
}

/*
 * Name:        stackChange
 * Purpose:     To execute the commands that change the top value of the stack
 * Parameters:  None
 * Returns:     None
 * Effects:     None
 */
void RPNCalc::stackChange(string cmd) {
    // Execute the specified command
    if (cmd == "dup") {
        dup();
    } else if (cmd == "drop") {
        drop();
    } else if (cmd == "swap") {
        swap();
    }
}

/*
 * Name:        dup
 * Purpose:     To duplicate the top datum on the stack
 * Parameters:  None
 * Returns:     None
 * Effects:     If stack is empty, throws a runtime error
 */
 void RPNCalc::dup() {
    if (not stack.isEmpty()) {
        stack.push(stack.top());
    } else {
        cerr << "Error: empty_stack\n"; 
    }
}

/*
 * Name:        drop
 * Purpose:     To remove the top datum on the stack
 * Parameters:  None
 * Returns:     None
 * Effects:     If stack is empty, throws a runtime error
 */
 void RPNCalc::drop() {
    try {
        // Attempt to pop datum off the stack
        Datum element1 = stack.pop(); 
        
    // Catch any errors that stack.pop() may have throwm and cerr them    
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    }
}


/*
 * Name:        swap
 * Purpose:     To change the order of the top two items on the stack
 * Parameters:  None
 * Returns:     None
 * Effects:     If stack is empty or only has one item, throws a runtime error
 */
 void RPNCalc::swap() {
    try {
        // Attempt to pop two values from the stack
        Datum element1 = stack.pop();  
        Datum element2 = stack.pop(); 
        
        // Push them back onto the stack in reverse order
        stack.push(Datum(element1));
        stack.push(Datum(element2));
    
    // Catch any errors that stack.pop() may have throwm and cerr them    
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    }
}

/*
 * Name:        doMath
 * Purpose:     Does the arithmetic operation on the top to Datum objects of 
 *              the stack
 * Parameters:  The given arithemetic operation
 * Returns:     None
 * Effects:     Pops of first two items from the stack and pushes the result of
 *              the given operation, if not possible, outputs an error
*/
 void RPNCalc::doMath(std::string op) {
    try {
        // Attempt to pop two values from the stack
        Datum num2 = stack.pop();  
        Datum num1 = stack.pop();  

        // Do arithmetic operations
        if (num1.isInt() and num2.isInt()) {
            if (op == "+") {
                stack.push(Datum(num1.getInt() + num2.getInt()));
            } else if (op == "-") {
                stack.push(Datum(num1.getInt() - num2.getInt()));
            } else if (op == "*") {
                stack.push(Datum(num1.getInt() * num2.getInt()));
            } else if (num2.getInt() == 0) {
                cerr << "Error: division by 0.\n";
                return;
            } else if (op == "/") {
                stack.push(Datum(num1.getInt() / num2.getInt()));
            } else if (op == "mod") {
                stack.push(Datum(num1.getInt() % num2.getInt()));
            }
        
        // Output to cerr if trying to compare values of non-numbers
        } else {
            cerr << "Error: datum_not_int\n";
        }
       
    // Catch any errors that stack.pop may have thrown
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    }
 }
 
/*
 * Name:        relate
 * Purpose:     Eelates the top to Datum objects on the stack
 * Parameters:  The given relation
 * Returns:     None
 * Effects:     Pops of first two items from the stack and pushes the result of
 *              the given relationship, if not possible, outputs an error
*/
void RPNCalc::relate(std::string op) {
    try {
        // Attempt to pop two values from the stack
        Datum num2 = stack.pop();  
        Datum num1 = stack.pop();  

        // Evaluate the numerical relationships
        if (num1.isInt() and num2.isInt()) {
            if (op == ">") {
                stack.push(Datum(num1.getInt() > num2.getInt()));
            } else if (op == "<") {
                stack.push(Datum(num1.getInt() < num2.getInt()));
            } else if (op == ">=") {
                stack.push(Datum(num1.getInt() >= num2.getInt()));
            } else if (op == "<=") {
                stack.push(Datum(num1.getInt() <= num2.getInt()));
            }
        
        // Output to cerr if trying to compare values of non-numbers
        } else {
            cerr << "Error: datum_not_int\n";
        }
        
    // Catch any errors that stack.pop may have thrown and cerr what happened
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    }
}

/*
 * Name:        equate
 * Purpose:     Equates the top to Datum objects on the stack
 * Parameters:  None
 * Returns:     None
 * Effects:     Pops of first two items from the stack and pushes whether or
 *              not they're equal, if not possible, outputs an error
*/
void RPNCalc::equate() {
    try {
        // Attempt to pop two values from the stack
        Datum element2 = stack.pop();  
        Datum element1 = stack.pop();  
        
        // Evaluate the equality of the two datum objects
        stack.push(Datum(element1 == element2));
    
    // Catch any errors that stack.pop may have thrown and cerr what happened
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    }
}

/*
 * Name:        stackNot
 * Purpose:     To inverse the value of the top datum on the stack
 * Parameters:  None
 * Returns:     None
 * Effects:     Inverts value of top item on the stack, only works for booleans
 *              Otherwise throws a runtime error
 */
 void RPNCalc::stackNot() {
    try {
        // Attempt to pop two values from the stack
        Datum bool1 = stack.pop();
        
        // Invert the booleans
        if (bool1.isBool()) {
            if (bool1.getBool()) {
                stack.push(Datum(false));
            } else {
                stack.push(Datum(true));
            }
        
        // Output to cerr if trying to compare values of non-numbers
        } else {
            cerr << "Error: datum_not_int\n";
        }
    
    // Catch any errors that stack.pop may have thrown and cerr what happened
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
    } 
}

/*
 * Name:        convertBool
 * Purpose:     Push boolean value that stack rstring represents onto the stack
 * Parameters:  None
 * Returns:     None
 * Effects:     Throws a runtime error if the rstring is improperly formatted.
 */
void RPNCalc::convertBool(string boolean) {
    // Take in value of CalcYouLater boolean and convert to actual boolean
    if (boolean[1] == 't') {
        stack.push(Datum(true));
    } else if (boolean[1] == 'f') {
        stack.push(Datum(false));
    
    // If not a properly formatted CalcYouLater boolean, output to cerr
    } else {
        cerr << "Error: invalid boolean" << boolean << endl;
    }
}

/*
 * Name:       got_int 
 * Purpose:    determines whether a string contains an encoding of an
 *             integer value and loads said integer into an integer
 *             variable whose address has been passed to this function.
 *             An integer encoding contains an optional sign and
 *             a sequence of digits.  Extraneous whitespace is
 *             ignored.
 * Parameters: s contains a string that might encode an integer.
 *             resultp contains the address of an integer variable to
 *             store the integer from s in, should the conversion
 *             succeed. Can be parsed from said string
 * Returns:    true if an integer was successfully parsed from the
 *             provided string;
 *             false otherwise (s did not contain a valid integer
 *             encoding)
 * Effects:    *resultp will be set the integer value encoded by s
 *             on success; otherwise it is undetermined (may be set
 *             if there are extra characters after digits)
 *
 * Author: Mark A. Sheldon, Tufts University, Fall 2016
 * Note to students: you do not have to modify this comment!
 */
 bool RPNCalc::got_int(string s, int *resultp) {
    char extra;  /* Holds first non-whitespace character after integer */
                 /* Should not match anything:  want "3." to fail      */
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}