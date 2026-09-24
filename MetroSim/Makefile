#########################################################
#             PROJECT 1: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# ***TODO***
# Write rules for any other .o files.
# You can base them on the PassengerQueue.o rule.
# Every .cpp file that is part of your program should have a .o rule.


# ***TODO***
# Metrosim rule - you need to fill in the linking command,
# add any new dependencies, and add target rules for 
# Passenger.o, MetroSim.o, main.o, and any new dependencies.
# Please use the rules provided below for PassengerQueue.o as an example for
# what to do.
# If you add other classes, you'll have to add their .o files as dependencies here.
# Don't forget:  the clang++ command must be indented with a TAB character
# and be all on one line.

# Final executable
MetroSim: main.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(CXXFLAGS) -o MetroSim MetroSim.o PassengerQueue.o Passenger.o main.cpp

# Pattern rule for compiling .cpp files into .o files
%.o: %.cpp %.h
	$(CXX) $(LDFLAGS) -c $<

# Special rule for main.o (no header needed)
main.o: main.cpp
	$(CXX) $(LDFLAGS) -c main.cpp

# Unit test target
unit_test: unit_test_driver.o PassengerQueue.o Passenger.o
	$(CXX) $(LDFLAGS) -o unit_test $^

# Clean command to remove compiled files
clean:
	rm -f *.o MetroSim unit_test


# MetroSim: main.cpp MetroSim.o PassengerQueue.o Passenger.o Station.o
# 	${CXX} ${LDFLAGS} -o MetroSim MetroSim.o PassengerQueue.o Passenger.o Station.o TrainCar.o main.cpp 

# # This rule builds MetroSim.o
# MetroSim.o: MetroSim.cpp MetroSim.h PassengerQueue.h Passenger.h
# 	${CXX} ${LDFLAGS} -c MetroSim.cpp MetroSim.h PassengerQueue.cpp Passenger.cpp 

# # This rule builds Station.o
# Station.o: Station.cpp Station.h PassengerQueue.h 
# 	$(CXX) $(CXXFLAGS) -c Station.cpp PassengerQueue.cpp

# # This rule builds TrainCar.o
# TrainCar.o: TrainCar.cpp TrainCar.h PassengerQueue.h 
# 	$(CXX) $(CXXFLAGS) -c TrainCar.cpp PassengerQueue.cpp


# # This rule builds PassengerQueue.o
# PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h
# 	$(CXX) $(CXXFLAGS) -c PassengerQueue.cpp


# # This rule builds PassengerQueue.o
# Passenger.o: Passenger.cpp Passenger.h 
# 	$(CXX) $(CXXFLAGS) -c Passenger.cpp

# # ***TODO***
# # The below rule will be used by unit_test.
# # Please add any other .o files that are needed by PassengerQueue,
# # and any other .o files you wish to test. 
# unit_test: unit_test_driver.o PassengerQueue.o Passenger.o
# 	$(CXX) $(CXXFLAGS) $^/*

# # remove executables, object code, and temporary files from the current folder 
# # -- the executable created by unit_test is called a.out
# clean: 
# 	rm *.o *~ a.out
