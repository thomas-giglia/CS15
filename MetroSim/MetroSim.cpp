/*
 *  MetroSim.cpp
 *  
 *  2/9/2025
 *
 *  Metro Sim
 *
 *  PURPOSE: The MetroSim program simulates a subway or metro system where 
 *           passengers can board and deboard trains at different stations. 
 *           It allows for input from either a file or user input, handles 
 *           passenger movement between stations and trains, and outputs the 
 *           state of the system to a specified output file.
 */  

#include "MetroSim.h"

using namespace std;


/*
 * name:      MetroSim
 * purpose:   Default constructor for MetroSim
 * arguments: none
 * returns:   none
 * effects:   Initializes an empty MetroSim instance.
 */
MetroSim::MetroSim() {}

/*
 * name:      MetroSim
 * purpose:   Constructs MetroSim and initializes stations from a file.
 * arguments: inputFile - the name of the stations file
 * returns:   none
 * effects:   Reads station names from the input file and initializes the 
 * corresponding data structures (stations and trains).
 */
MetroSim::MetroSim(string inputFile) {
    checkInput(inputFile);  // Ensure input file can be opened
    ifstream stationList(inputFile); // Open the station list file

    string name;
    int count = 0;

    // Loop through each line in the file, reading station names
    while (getline(stationList, name)) {
        if (not name.empty()) {  // Ignore empty lines
            QueueData tempStations;
            stations.push_back(tempStations);  // Add a station to the list
            stations[count].name = name;      
            stations[count].id = count;  

            QueueData tempTrain;
            train.push_back(tempTrain);        
            train[count].id = count;          
            
            count++;
        }
    }
    stationList.close();  // Close the station file
}

/*
 * name:      run
 * purpose:   Runs the MetroSim simulation.
 * arguments: outputFile - the file name to output the simulation state
 *            cmdFile - the command file that provides simulation commands
 * returns:   none
 * effects:   Reads commands from the provided command file or standard input 
 * and processes the simulation steps.
 */
void MetroSim::run(string outputFile, string cmdFile) {
    string input;
    istream *inputStream;
    ifstream fileInput;
    ofstream output(outputFile);  // Open the output file for logging
    
    if (cmdFile == "cin") {
        inputStream = &cin;
    } else {
        checkInput(cmdFile);  // Ensure the command file can be opened
        fileInput.open(cmdFile);  // Open the command file
        inputStream = &fileInput;
    }

    printState();  // Print the initial state of the simulation
    while (getline(*inputStream, input)) {
        commandLoop(input, output);
    }

    // Close the input file if opened
    if (fileInput.is_open()) { 
        fileInput.close();
    }
}

/*
 * name:      commandLoop
 * purpose:   Processes a single command from input.
 * arguments: input - the command string
 *            output - output stream for logging
 * returns:   none
 * effects:   Executes actions based on the command input (e.g., 
 *            adding passengers, moving trains).
 */
void MetroSim::commandLoop(string input, ostream &output) {
    if (input[0] == 'p' and input.length() > 4) {
        addPassenger(input); 
    } else if (input[0] == 'm' and input[2] == 'm') {
        allAboard(output);
        currStation = (currStation + 1) % stations.size();
        mindTheGap(output);
    } else if (input[0] == 'm' and input[2] == 'f') {
        cout << "Thanks for playing MetroSim. Have a nice day!" << endl;  
        return; // End the simulation
    }
    printState();  // Print the updated state of the simulation
}

/*
 * name:      addPassenger
 * purpose:   Adds a new passenger to the simulation.
 * arguments: input - command string containing passenger data
 * returns:   none
 * effects:   Parses the input to extract arrival and destination stations, 
 *            then enqueues the passenger to the appropriate station.
 */
void MetroSim::addPassenger(string input) {
    int arr;
    int dest;
    string temp = "";
    
    // Parse the command string to extract the arrival and destination stations
    for (int i = 2; i < input.length(); i++) {
        if (input[i] != ' ') {
            temp += input[i];  // Accumulate digits for arrival station
        } else {
            arr = stoi(temp);  // Convert arrival station to integer
            temp = "";
        }
    }
    dest = stoi(temp);  // Convert destination station to integer
    
    Passenger p(idCount, arr, dest);
    stations[arr].queue.enqueue(p);  // Add passenger to station's queue
    idCount++;
}

/*
 * name:      allAboard
 * purpose:   Moves passengers from station to train.
 * arguments: output - output stream for logging
 * returns:   none
 * effects:   Transfers all passengers at the current station to the train
 */
void MetroSim::allAboard(ostream &output) {
    int queueSize = stations[currStation].queue.size();  
    for (int i = 0; i < queueSize; i++) {
    Passenger p = stations[currStation].queue.front();  // 1st passenger
    train[p.getEndingStation()].queue.enqueue(p);  
    stations[currStation].queue.dequeue();  // Remove passenger from queue
    }
}

/*
 * name:      mindTheGap
 * purpose:   Unloads passengers from train at current station.
 * arguments: output - output stream for logging
 * returns:   none
 * effects:   Removes passengers from the train if they have reached their 
 *            destination.
 */
void MetroSim::mindTheGap(ostream &output) {
    int queueSize = train[currStation].queue.size(); 
    for (int j = 0; j < queueSize; j++) {
        Passenger p2 = train[currStation].queue.front(); // 1st passenger
        output << "Passenger " << p2.getId() << " left train at station ";
        output << stations[p2.getEndingStation()].name << endl; 
        train[currStation].queue.dequeue();  // Remove passenger from queue
    }
}

/*
 * name:      printState
 * purpose:   Prints the current state of the simulation.
 * arguments: none
 * returns:   none
 * effects:   Displays the current passengers on the train and at each 
 *            station, as well as the command prompt.
 */
void MetroSim::printState() {
    cout << "Passengers on the train: {";
    // Print passengers at each train
    for (int i = 0; i < train.size(); i++) {
        train[i].queue.print(cout);  
    }
    cout << "}" << endl;
    
    // Print each station's state
    for (int j = 0; j < stations.size(); j++) {
        if (currStation == j) {
            cout << "TRAIN: ";  // Mark station where train is located
        } else {
            cout << "       ";  // Indent other stations
        }
        cout << "[" << j << "] " << stations[j].name << " {";
        stations[j].queue.print(cout);  // Print passengers at the station
        cout << "}" << endl; 
    }
    cout << "Command? ";
}

/*
 * name:      checkInput
 * purpose:   checks that a file can be opened for reading from
 * arguments: the name of the file to check
 * returns:   none
 * effects:   throws an error if the file cannot be opened
 */
void MetroSim::checkInput(string filename){
ifstream input(filename);

if (not input.is_open()) {
    cerr << "Error: could not open file " << filename << endl;
    exit(EXIT_FAILURE);
}
input.close();    
}

/*
 * name:      checkOutput
 * purpose:   checks that a file can be opened for reading from
 * arguments: the name of the file to check
 * returns:   none
 * effects:   throws an error if the file cannot be opened
 */
void MetroSim::checkOutput(string filename){
    ofstream output(filename);
    
    if (not output.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
    output.close();    
}
