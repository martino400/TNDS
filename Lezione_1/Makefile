CXXFLAGS = -g3 -Wall --pedantic -std=c++20

esercizio1.1: esercizio1.1.o funzioni.o
	g++ esercizio1.3.o funzioni.o -o esercizio1.1 $(CXXFLAGS)

esercizio1.1.o: esercizio1.1.cpp funzioni.h
	g++ -c esercizio1.1.cpp -o esercizio1.1.o $(CXXFLAGS)

funzioni.o: funzioni.cpp funzioni.h
	g++ -c funzioni.cpp -o funzioni.o $(CXXFLAGS)

