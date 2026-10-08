CXXFLAGS = -g3 -Wall --pedantic -std=c++20

esercizio1.3: esercizio1.3.o funzioni.o
	g++ esercizio1.3.o funzioni.o -o esercizio1.3 $(CXXFLAGS)

esercizio1.3.o: esercizio1.3.cpp funzioni.h
	g++ -c esercizio1.3.cpp -o esercizio1.3.o $(CXXFLAGS)

funzioni.o: funzioni.cpp funzioni.h
	g++ -c funzioni.cpp -o funzioni.o $(CXXFLAGS)

