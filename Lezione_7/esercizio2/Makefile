CXXFLAGS=-g -Wall --pedantic -std=c++23

all: esercizio7.2 esercizio7.1 esercizio7.0

esercizio7.2: esercizio7.2.cpp funzionebase.h integral.h
	g++ -o esercizio7.2 esercizio7.2.cpp ${CXXFLAGS}

esercizio7.0: esercizio7.2.cpp funzionebase.h integral.h
	g++ -o esercizio7.2 esercizio7.2.cpp ${CXXFLAGS}

esercizio7.1: esercizio7.2.cpp funzionebase.h integral.h
	g++ -o esercizio7.2 esercizio7.2.cpp ${CXXFLAGS}

clean:
	rm -f *.o