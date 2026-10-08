#include <iostream>
#include <fstream>
#include <string>
#include "posizione.h"

#include "fmtlib.h"

using namespace std;
using namespace fmt;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        println("Errore con il programma, mancano argomenti da inserire !!");
        return -1;
    }

    double x{stod(argv[1])};
    double y{stod(argv[2])};
    double z{stod(argv[3])};

    posizione p{x, y, z};


    println("Coordinate cartesiane: {} , {} , {}\n", p.getX(), p.getY(), p.getZ());
    println("Coordinate sferiche: {} , {} , {}\n", p.getR(), p.getPhi(), p.getTheta());
    println("Coordinate cilindriche: {} , {} , {}\n", p.getPhi(), p.getZ(), p.getRho());

    return 0;
}
