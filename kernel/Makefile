CXX=g++
CXXFLAGS=-Os -Wall -fno-rtti -fno-exceptions -fno-unwind-tables -march=i386

all: kernel.o

kernel.o: KScheduler.o KPortMap.o KPort.o KThread.o machine/Machine.o
	ld -r -o $@ $^

include Makefile.dependencies

KScheduler.o: KScheduler.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KPortMap.o: KPortMap.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KPort.o: KPort.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KThread.o: KThread.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

machine/Machine.o: machine/Machine.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Makefile.dependencies:
	echo "" > Makefile.dependencies
	$(CXX) -MM KScheduler.cpp -o - >> Makefile.dependencies
	$(CXX) -MM KPortMap.cpp -o - >> Makefile.dependencies
	$(CXX) -MM KPort.cpp -o - >> Makefile.dependencies
	$(CXX) -MM KThread.cpp -o - >> Makefile.dependencies
	$(CXX) -MM machine/Machine.cpp -o - >> Makefile.dependencies

.PHONY clean:
	rm -f *.o machine/*.o Makefile.dependencies
