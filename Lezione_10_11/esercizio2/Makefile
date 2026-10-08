CXXFLAGS=-g -Wall --pedantic -std=c++23

esercizio10.2: esercizio10.2.cpp RandomGen.h gplot++.h IntegralMC.h funzionebase.h
	g++ -o esercizio10.2 esercizio10.2.cpp  ${CXXFLAGS}
	
esercizio10.2bis: esercizio10.2bis.cpp RandomGen.h gplot++.h IntegralMC.h funzionebase.h
	g++ -o esercizio10.2bis esercizio10.2bis.cpp  ${CXXFLAGS}


clean:
	rm -f *.o
	rm esercizio10.2
	rm esercizio10.2bis

all:
	esercizio10.2 \
	esercizio10.2bis