# Makefile for CS 455 PA5
#
#
#     make concord
#        Makes concord executable
#
#     make grades
#        Makes grades executable
#
#     make pa5list
#	     Makes pa5list executable.  (This is a test driver for your list functions)
#
#     make clean
#        Removes out .o files and executables
#
#

# compile options to be used in all compile commands
#     NOTE: $(CXXFLAGS) in the compile commands below will be replaced by the options after the =
CXXFLAGS = -ggdb -Wall -Wno-sign-compare -std=c++11


concord: concord.o Table.o listFuncs.o
	g++ $(CXXFLAGS) -o concord concord.o Table.o listFuncs.o

grades: grades.o Table.o listFuncs.o
	g++ $(CXXFLAGS) -o grades grades.o Table.o listFuncs.o

pa5list: pa5list.cpp listFuncs.o listFuncs.h Table.o
	g++ $(CXXFLAGS) pa5list.cpp listFuncs.o Table.o -o pa5list

concord.o: concord.cpp Table.h
	g++ $(CXXFLAGS) -c concord.cpp

Table.o: Table.cpp Table.h listFuncs.h
	g++ $(CXXFLAGS) -c Table.cpp

grades.o: grades.cpp Table.h
	g++ $(CXXFLAGS) -c grades.cpp

listFuncs.o: listFuncs.cpp listFuncs.h
	g++ $(CXXFLAGS) -c listFuncs.cpp

clean:
	-rm -f concord grades pa5list concord.o Table.o listFuncs.o grades.o
