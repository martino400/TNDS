LIBS := `root-config --libs`
CXXFLAGS :=  `root-config --cflags` -g3 -Wall --pedantic -std=c++20

esame: appello5.cpp VectorOperations.h FunzioneVettoriale.h gplot++.h funzionebase.h fmtlib.h RandomGen.h Esperimento.h
	g++ -o esame appello5.cpp  ${CXXFLAGS} ${LIBS}

clean:
	rm -f *.o