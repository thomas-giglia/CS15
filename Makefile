
#   HuffmanCoder.cpp
#   Thomas Giglia
#   4/1/2025
#
#   COMP 15 Project 3 Zap!
# 
#  	PURPOSE: Simple to execute compilation of the files necessary to run the
# 	program and cleaning of unnecessary .o files afterwards.

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# Rule for zap executable
zap: main.o HuffmanCoder.o HuffmanTreeNode.o ZapUtil.o
	${CXX} ${LDFLAGS} -o zap main.o HuffmanCoder.o HuffmanTreeNode.o ZapUtil.o

# Rule for main.o
main.o: main.cpp HuffmanCoder.h
	${CXX} ${CXXFLAGS} -c main.cpp


# Rule for HuffmanCoder.o 
HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h ZapUtil.h
	${CXX} ${CXXFLAGS} -c HuffmanCoder.cpp

# Rule for unit_test
unit_test: unit_test_driver.o HuffmanCoder.o HuffmanTreeNode.o ZapUtil.o
	${CXX} ${LDFLAGS} -o a.out unit_test_driver.o HuffmanCoder.o HuffmanTreeNode.o ZapUtil.o

# Rule for unit_test_driver.o
unit_test_driver.o: unit_test_driver.cpp phaseOne.h
	${CXX} ${CXXFLAGS} -c unit_test_driver.cpp



##
## Here is a special rule that removes all .o files besides the provided ones 
## (ZapUtil.o and HuffmanTreeNode.o), all temporary files 
## (ending with ~), and a.out produced by running unit_test. First, we find
## all .o files that are not provided files, then we run rm -f on each found
## file using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'HuffmanTreeNode.o' \
		! -name 'ZapUtil.o' \) -exec rm -f {} \;
	@rm -f *~ a.out

