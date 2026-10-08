LIBS := `root-config --libs`
CXXFLAGS :=  `root-config --cflags` -g3 -Wall --pedantic -std=c++20

esercizio4.2: esercizio4.2.cpp funzioni.h
	g++ -o esercizio4.2 esercizio4.2.cpp ${CXXFLAGS} ${LIBS}

clean:
	rm -f esercizio4.2