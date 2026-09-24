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
     string temp = "";
     while (cont) {
         string input = readIntoString(cin);
         pushPrep(input);
     }
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
         if ((temp[i] == ' ' or temp[i] == '\n') and nestLvl == 0) {
             if (input == "quit") return input;
             push(input);
             input = "";
         } else if (temp[i] == '{') {
             nestLvl++;
             if (nestLvl > 0) input += '{';
         } else if (temp[i] == '}') {
             nestLvl--;
             input += '}';
         } else{
             input += temp[i];
         }
     }
     return input;
 }
 
 /*
  * Name:        checkForCommands
  * Purpose:     Finds valid commands in inputs and runs them
  * Parameters:  The input from the user
  * Returns:     A string to push to the stack
  * Effects:     Outputs error if the command is unimplemented
  */
 void RPNCalc::findCommand(string cmd) {
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
     } else { 
         cerr << cmd << ": unimplemented\n";
     }
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
     while (getline(input, inputString)) { 
         if (inputString.length() > 0 and inputString[0] != ' ') {
             temp += " ";
         }
         temp += inputString; 
     }
     temp = "{" + temp + "}"; 
     int stringLength = temp.length();
     for (int i = 0; i < stringLength; i++) { 
         
         // protocols for getting characters but ignoring unnecessary whitespace
         if (temp[i] != '\n' and temp[i] != ' ') {
             rstring += temp[i];
         } else if ((temp[i] == ' ' and rstring[rstring.length()-1] != ' ')) {
             rstring += temp[i];
         }
         
         // protocols for if braces appear
         if (temp[i] == '{') {
             nestLvl++;
         } else if (temp[i] == '}') { // Stop parsing if '}' is found
             nestLvl--;
             if (nestLvl == 0) {
                 rstring = rstring.substr(2, rstring.length()-3);
                 return rstring; 
             }
         }
     }
     
     // add an additional space as the second to last character if necessary
     if (rstring[rstring.length() - 1] != ' ') rstring += " ";
     return rstring + "}";
 }
 
 /*
  * Name:        push
  * Purpose:     To add datum objects to the stack
  * Parameters:  An rstring representing the datum's value
  * Returns:     None
  * Effects:     Adds the datum to the stack
  */
 void RPNCalc::push(string substring) {
     int favNumber = 7;
     int* potInt = &favNumber;
     if (substring == "quit") {
         cont = false; 
         return;
     } else if (substring.length() == 0) {
         return;
     } else if (got_int(substring, potInt)){
         stack.push(Datum(*potInt));
     }else if (substring[0] == '#') {
         if (substring[1] == 't') {
             stack.push(Datum(true));
         } else if (substring[1] == 'f') {
             stack.push(Datum(false));
         } else {
             cerr << "Error: invalid boolean" << substring << endl;
         }
     } else if (substring[0] == '{') {
         stack.push(Datum(substring));
     } else {
         findCommand(substring);
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
     if (stack.isEmpty()) {
         cerr << "Error: empty_stack\n";
         return;
     } else if (stack.top().isInt()) {
         cout << stack.top().getInt() << endl;
     } else if (stack.top().isBool()) {
         if (stack.top().getBool()) {
             cout << "#t" << endl;
         } else {
             cout << "#f" << endl;
         }
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
         // Attempt to pop two values from the stack
         Datum executable = stack.pop();  
         if (not executable.isRString()) {
             throw runtime_error("Error: cannot execute non rstring\n");     
         } else {
             string rstring = executable.getRString();
             rstring = rstring.substr(2, rstring.length() - 3);
             rstring = read(rstring);
             
             push(rstring);
         }
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
     bool alreadyRead = false;
     try {
         // Attempt to pop two values from the stack
         Datum fileRString = stack.pop(); 
         if (not fileRString.isRString()) {
             cerr << "Error: file operand not rstring\n"; 
         } else {
             string filename = fileRString.getRString();
             filename = filename.substr(2, filename.length() - 4);
             ifstream fileStream(filename);  
             if (not fileStream.is_open()) {
                 cerr << "Unable to read " << filename << endl;
             } else if (not alreadyRead) {
                 pushPrep(readIntoString(fileStream));
                 cont = false;
                 fileStream.close();    
             }
         }
     } catch (const runtime_error &e) {
         cerr << e.what() << endl;
     }
 }
 
 /*
  * Name:        readIntoString
  * Purpose:     Reads in any commands from an istringstream and adds them to 
  *              the stack.
  * Parameters:  None
  * Returns:     None
  * Effects:     Add any data from the istringstrem to the stack. 
  */
 string RPNCalc::readIntoString(istream &fileStream) {
     list<string> commands;
     string input, temp = "";
 
     while (getline(fileStream, temp) and cont) {
         commands.push_back(temp + " ");
     }
 
     while (not commands.empty()) {
         string cmd = commands.front();
         commands.pop_front(); 
         input += " " + cmd.substr(0, cmd.length() - 2);
         char endChar = cmd[cmd.length() - 1];
         if (cmd.length() > 1) {
             char c2 = cmd[cmd.length() - 2];
             if (c2 >= '0' and c2 <= '9') {
                 input += c2;
             } else if (c2 >= 'a' and c2 <= 'z') {
                 input += c2;
             }
         }
         if (endChar >= '0' and endChar <= '9') {
             input += endChar;
         } else if (endChar >= 'a' and endChar <= 'z') {
             input += endChar;
         }
     }
     return input;
 }
 
 /*
  * Name:        pushPrep
  * Purpose:     Creates the proper datum objects to be added to the stack and
  *              pushes them.
  * Parameters:  None
  * Returns:     None
  * Effects:     Add any data from the commands to the stack. 
  */
 void RPNCalc::pushPrep(string commands) {
     //if 
     int test;
     int* potInt = &test;
     string input = read(commands);
     if (got_int(input, potInt)) {
         push(input);
     } else if (input[0] == '{') {    
         istringstream iss(input.substr(1));
         push(parse(iss));
     } else {
         push(input);
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
         if (not resultFalse.isRString()) {
             throw runtime_error("Error: expected rstring in if branch\n");   
         }
         if (not resultTrue.isRString()) {
             throw runtime_error("Error: expected rstring in if branch\n");   
         }
         if (not conditional.isBool()) {
             throw runtime_error("Error: expected boolean in if test\n");   
         }
         if (conditional.getBool()) {
             push(resultTrue.getRString());
         } else {
             push(resultFalse.getRString());
         }
         exec();
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
         Datum element1 = stack.pop();  
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
         stack.push(Datum(element1));
         stack.push(Datum(element2));
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
 
         if (num1.isInt() and num2.isInt()) {
             if (op == "+") {
                 stack.push(Datum(num1.getInt() + num2.getInt()));
             } else if (op == "-") {
                 stack.push(Datum(num1.getInt() - num2.getInt()));
             } else if (op == "*") {
                 stack.push(Datum(num1.getInt() * num2.getInt()));
             } else if (num2.getInt() == 0) {
                 cerr << "Error: divide_by_0\n";
                 return;
             } else if (op == "/") {
                 stack.push(Datum(num1.getInt() / num2.getInt()));
             } else if (op == "mod") {
                 stack.push(Datum(num1.getInt() % num2.getInt()));
             }
 
         } else {
             cerr << "Error: datum_not_int\n";
         }
         
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
         } else {
             cerr << "Error: datum_not_int\n";
         }
         
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
         stack.push(Datum(element1 == element2));
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
         if (bool1.isBool()) {
             if (bool1.getBool()) {
                 stack.push(Datum(false));
             } else {
                 stack.push(Datum(true));
             }
         } else {
             cerr << "Error: datum_not_int\n";
         }
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
     if (boolean[1] == 't') {
         stack.push(Datum(true));
     } else if (boolean[1] == 'f') {
         stack.push(Datum(false));
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