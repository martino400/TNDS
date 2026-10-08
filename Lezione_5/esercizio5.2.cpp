#include <iostream>
#include <fstream>
#include <string>
#include "posizione.h"
#include "particella.h"
#include "elettrone.h"


#include "fmtlib.h"

using namespace std;
using namespace fmt;

int main()
{
    particella a{1.2 , 1.3};
    //stampa VARIABILE
    a.Print();

    elettrone *e = new elettrone();
    //stampa PUNTATORE
    e->Print();

    particella b{a};
    particella c{*e};
    
    //elettrone ele{b}; //non funziona dimacane dimaporco perchè il costruttore funziona in modo diverso SVEGLIA






    return 0;
}
