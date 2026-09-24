###
### Makefile for Gerp Project
###
### Author:  Thomas Giglia


CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# Rule for gerp executable
gerp: main.o processing.o FSTree.o DirNode.o Gerp.o 
	${CXX} ${LDFLAGS} -o gerp main.o processing.o FSTree.o DirNode.o

# Rule for main.o
main.o: main.cpp processing.h Gerp.h
	${CXX} ${CXXFLAGS} -c main.cpp

# Rule for Gerp.o
Gerp.o: Gerp.cpp processing.h FSTree.h DirNode.h
	${CXX} ${CXXFLAGS} -c Gerp.cpp

# Rule for processing.o 
processing.o: processing.cpp FSTree.h DirNode.h
	${CXX} ${CXXFLAGS} -c processing.cpp

# Rule for unit_test
unit_test: unit_test_driver.o processing.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o a.out unit_test_driver.o processing.o FSTree.o DirNode.o

# Rule for unit_test_driver.o
unit_test_driver.o: unit_test_driver.cpp processing.h
	${CXX} ${CXXFLAGS} -c unit_test_driver.cpp



##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out

