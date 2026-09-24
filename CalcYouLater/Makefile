#  	Makefile
#  	Thomas Giglia
#  	2/9/2025
#
#  	COMP 15 Project 2 CalcYouLater
# 
# 
#  	PURPOSE: Simple to execute compilation of the files necessary to run the
# 	program and cleaning of unnecessary .o files afterwards.

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# Rule for main executable
CalcYouLater: main.o RPNCalc.o Datum.o DatumStack.o
	${CXX} ${LDFLAGS} -o CalcYouLater main.o RPNCalc.o Datum.o DatumStack.o

# Rule for main.o 
main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

# Rule for unit_test
unit_test: unit_test_driver.o Datum.o DatumStack.o
	${CXX} ${LDFLAGS} -o unit_test unit_test_driver.o Datum.o DatumStack.o

# Rule for DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h
	${CXX} ${CXXFLAGS} -c DatumStack.cpp

# Rule for RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h
	${CXX} ${CXXFLAGS} -c RPNCalc.cpp

# Generic cleanup rule
clean:
	@rm -f *.o main unit_test example *~ 

# Rule for compiling .cyl files for use in testing
%.cylc: %.cyl
	./cylc $^
