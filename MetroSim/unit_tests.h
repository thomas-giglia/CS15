#include "MetroSim.h"
#include <cassert>
#include <fstream>

// Unit test for Passenger constructor, simply tests that no errors are thrown
void testPassengerConstructor() {
    Passenger p1(1, 10, 20);
    Passenger p2(2, 5, 15);
    Passenger p3(3, 0, 50);
}

// Tests that getId function works properly and that IDs are incrementing as
// expected.
void getIdTest() {
    Passenger p1(1, 10, 20);
    Passenger p2(2, 5, 15);
    Passenger p3(3, 0, 50);
    assert(p1.getId() == 1);
    assert(p2.getId() == 2);
    assert(p3.getId() == 3);
}

// Tests that getStartingStation function works properly and that ending
// stations are being stored as expected even with enqueues and dequeues
void getStartingStationTest() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    Passenger p2(2, 5, 15);
    Passenger p3(3, 1, 50);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    Passenger dequeued = pq.dequeue();
    assert(dequeued.getStartingStation() == 10);
    assert(p2.getStartingStation() == 5);
    assert(p3.getStartingStation() == 1);
}

// Tests that getEndingStation function works properly and that ending stations
// are being stored as expected even with enqueues and dequeues
void getEndingStationTest() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    Passenger p2(2, 5, 15);
    Passenger p3(3, 1, 50);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    Passenger dequeued = pq.dequeue();
    assert(dequeued.getEndingStation() == 20);
    assert(p2.getEndingStation() == 15);
    Passenger dequeued2 = pq.dequeue();
    assert(dequeued2.getEndingStation() == 15);
    assert(p3.getEndingStation() == 50);
}

// Test: Print a single passenger and verify the correct formatted output.
 void testPrintSinglePassenger() {
    Passenger p(1, 10, 20);
    std::ostringstream output;
    p.print(output);
    assert(output.str() == "[1, 10->20]");
}

// Test: Print a passenger with different station values to check formatting.
void testPrintDifferentStations() {
    Passenger p(2, 5, 30);
    std::ostringstream output;
    p.print(output);
    assert(output.str() == "[2, 5->30]");
}


// Test: Print a passenger with zero as a station number to check edge cases.
void testPrintZeroStation() {
    Passenger p(3, 0, 50);
    std::ostringstream output;
    p.print(output);
    assert(output.str() == "[3, 0->50]");
}

// Test: Print multiple passengers to verify independent formatting.
void testPrintMultiplePassengers() {
    Passenger p1(4, 12, 18);
    Passenger p2(5, 7, 22);
    std::ostringstream output1, output2;
    p1.print(output1);
    p2.print(output2);
    assert(output1.str() == "[4, 12->18]");
    assert(output2.str() == "[5, 7->22]");
}

// Test: Call front on a queue with a single passenger and verify it returns 
// the correct passenger.
 void testFrontSinglePassenger() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    pq.enqueue(p1);
    assert(pq.front().getId() == 1);
    assert(pq.front().getStartingStation() == 10);
    assert(pq.front().getEndingStation() == 20);
}

// Test: Call front on a queue with multiple passengers and verify it always 
// returns the first passenger.
void testFrontMultiplePassengers() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    Passenger p2(2, 15, 25);
    pq.enqueue(p1);
    pq.enqueue(p2);
    assert(pq.front().getId() == 1);
    assert(pq.front().getStartingStation() == 10);
    assert(pq.front().getEndingStation() == 20);
}

// Test: Enqueue a single passenger and check if it exists in the queue.
 void testEnqueueSinglePassenger() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    pq.enqueue(p1);
    //assert(pq.print() == "[1, 10->20] ");
}

// Test: Enqueue multiple passengers and check if they are added in order.
void testEnqueueMultiplePassengers() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    Passenger p2(2, 15, 25);
    pq.enqueue(p1);
    pq.enqueue(p2);
    //assert(pq.print() == "[1, 10->20] [2, 15->25] ");
}

// Test: Enqueue a passenger and then dequeue to verify proper order.
void testEnqueueAndDequeue() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    pq.enqueue(p1);
    Passenger dequeued = pq.dequeue();
    assert(dequeued.getId() == 1);
}

// Test: Dequeue a single passenger and check if it is the correct one.
void testDequeueSinglePassenger() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    pq.enqueue(p1);
    Passenger dequeued = pq.dequeue();
    assert(dequeued.getId() == 1);
}

// Test: Dequeue multiple passengers and verify FIFO order.
void testDequeueMultiplePassengers() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    Passenger p2(2, 15, 25);
    pq.enqueue(p1);
    pq.enqueue(p2);
    assert(pq.dequeue().getId() == 1);
    assert(pq.dequeue().getId() == 2);
}

// Test: Attempt to dequeue from an empty queue and check for error handling.
void testDequeueEmptyQueue() {
    PassengerQueue pq;
    try {
        pq.dequeue();
        assert(false); // Should not reach this point
    } catch (const std::runtime_error &e) {
        assert(true); // Exception should be thrown
    }
}

// Test: Check the size of an empty PassengerQueue.
// This verifies that the initial size of the queue is 0.
void testSizeEmptyQueue() {
    PassengerQueue pq;
    assert(pq.size() == 0);
}

// Test: Add a passenger to the queue and check if size updates correctly.
// Ensures that enqueue correctly increases the queue size.
void testSizeAfterEnqueue() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    pq.enqueue(p1);
    assert(pq.size() == 1);
}

// Test: Enqueue and dequeue operations affect the size as expected.
// Ensures that enqueue increases the size and dequeue decreases it.
void testSizeAfterDequeue() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    Passenger p2(2, 15, 25);
    pq.enqueue(p1);
    pq.enqueue(p2);
    assert(pq.size() == 2);
    pq.dequeue();
    assert(pq.size() == 1);
    pq.dequeue();
    assert(pq.size() == 0);
}

// Test: prints out an empty queue and makes sure that nothing is output.
// Outputs to a .txt file to be diff tested in after running.

void testPrintEmptyQueue() {
    PassengerQueue pq;
    std::string filename = "output_test1.txt";
    std::ofstream output(filename);
    if (not output.is_open()) {
        std::cerr << "Error: could not open file " << filename;
        exit(EXIT_FAILURE);
    }
    pq.print(output);
    output.close();
}


// Test: Enqueue a single passenger and verify the string representation.
// Outputs to a .txt file to be diff tested in after running.
void testQueuePrintSinglePassenger() {
    PassengerQueue pq;
    Passenger p1(1, 13, 17);
    pq.enqueue(p1);
    std::string filename = "output_test2.txt";
    std::ofstream output(filename);
    if (not output.is_open()) {
        std::cerr << "Error: could not open file " << filename;
        exit(EXIT_FAILURE);
    }
    pq.print(output);
    output.close();
}

// Test: Enqueue multiple passengers and verify the formatted output.
// Outputs to a .txt file to be diff tested in after running.
void testQueuePrintMultiplePassengers() {
    PassengerQueue pq;
    Passenger p1(1, 10, 20);
    Passenger p2(2, 15, 25);
    pq.enqueue(p1);
    pq.enqueue(p2);
    std::string filename = "output_test3.txt";
    std::ofstream output(filename);
    if (not output.is_open()) {
        std::cerr << "Error: could not open file " << filename;
        exit(EXIT_FAILURE);
    }
    pq.print(output);
    output.close();
}