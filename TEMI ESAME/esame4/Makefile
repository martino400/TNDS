LIBS := `root-config --libs`
CXXFLAGS :=  `root-config --cflags` -g3 -Wall --pedantic -std=c++20

esame: appello4.cpp VectorOperations.h FunzioneVettoriale.h gplot++.h funzionebase.h fmtlib.h RandomGen.h Esperimento.h integral.h
	g++ -o esame appello4.cpp  ${CXXFLAGS} ${LIBS}

clean:
	rm -f *.o