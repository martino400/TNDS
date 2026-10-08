LIBS := `root-config --libs`
CXXFLAGS :=  `root-config --cflags` -g3 -Wall --pedantic -std=c++20

esercizio3.2: esercizio3.2.cpp funzioni.h
	g++ -o esercizio3.2 esercizio3.2.cpp ${CXXFLAGS} ${LIBS}

clean:
	rm -f esercizio3.2