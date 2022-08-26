COMPILER = g++
MAKE_O_FILE = -c

all: test solver inOut consoleline
	$(COMPILER) $(MAKE_O_FILE) Main.cpp
	$(COMPILER) Main.o UnitTest.o SolveEq.o InAndOut.o ConsoleHandler.o -o Start.exe
	
test:
	$(COMPILER) $(MAKE_O_FILE) UnitTest.cpp

solver:
	$(COMPILER) $(MAKE_O_FILE) SolveEq.cpp

inOut:	
	$(COMPILER) $(MAKE_O_FILE) InAndOut.cpp

consoleline:
	$(COMPILER) $(MAKE_O_FILE) ConsoleHandler.cpp

makeDocum:
	doxygen DoxygenManifest