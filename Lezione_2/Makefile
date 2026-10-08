CXXFLAGS = -g3 -Wall --pedantic -std=c++20

esercizio2.1: esercizio2.1.o Vettore.o funzioni.o
	g++ -o esercizio2.1 esercizio2.1.o Vettore.o funzioni.o 
funzioni.o: funzioni.cpp funzioni.h Vettore.h
	g++ -c -o funzioni.o funzioni.cpp
esercizio2.1.o: esercizio2.1.cpp funzioni.h Vettore.h
	g++ -c -o esercizio2.1.o esercizio2.1.cpp
Vettore.o: Vettore.cpp Vettore.h
	g++ -c -o Vettore.o Vettore.cpp

clean:
	rm *.o
cleanall: clean
	rm esercizio2.1