CXX=g++
CXXFLAGS=-Os -Wall -ffreestanding -fno-rtti -fno-exceptions -fno-unwind-tables

all: kernel.o

kernel.o: KScheduler.o KPortMap.o KPort.o KThread.o KCore.o KMemory.o machine/Machine.o machine/x86_64.o Entry.o
	ld -r -o $@ $^

include Makefile.dependencies

KScheduler.o: KScheduler.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KPortMap.o: KPortMap.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KPort.o: KPort.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KCore.o: KCore.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KThread.o: KThread.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KMemory.o: KMemory.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Entry.o: Entry.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

machine/Machine.o: machine/Machine.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

machine/x86_64.o: machine/x86_64.s
	as -o $@ $<

Makefile.dependencies:
	echo "" > Makefile.dependencies
	$(CXX) -MM KScheduler.cpp -o - >> Makefile.dependencies
	$(CXX) -MM KPortMap.cpp -o - >> Makefile.dependencies
	$(CXX) -MM KPort.cpp -o - >> Makefile.dependencies
	$(CXX) -MM KThread.cpp -o - >> Makefile.dependencies
	$(CXX) -MM KMemory.cpp -o - >> Makefile.dependencies
	$(CXX) -MM KCore.cpp -o - >> Makefile.dependencies
	$(CXX) -MM Entry.cpp -o - >> Makefile.dependencies
	$(CXX) -MM machine/Machine.cpp -o - >> Makefile.dependencies

.PHONY clean:
	rm -f *.o machine/*.o Makefile.dependencies
