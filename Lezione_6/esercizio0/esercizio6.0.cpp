#include <iostream>
#include "particella.h"
#include "elettrone.h"

int main()
{
    particella *p{new particella{1., 2.}};
    elettrone *e{new elettrone{}};
    particella *g{new elettrone{}}; //puntatore di particella che punta a un elettrone

    p->Print();
    e->Print();
    g->Print();

    delete p;
    delete e;
    delete g;

    return 0;
}