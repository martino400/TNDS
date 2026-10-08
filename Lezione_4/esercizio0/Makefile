LIBS := `root-config --libs`
CXXFLAGS :=  `root-config --cflags` -g3 -Wall --pedantic -std=c++20

esercizio4.0: esercizio4.0.cpp funzioni.h
	g++ -o esercizio4.0 esercizio4.0.cpp ${CXXFLAGS} ${LIBS}

clean:
	rm -f esercizio4.0