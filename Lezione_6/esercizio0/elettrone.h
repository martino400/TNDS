#pragma once
#include <iostream>
#include <cmath>
#include "fmtlib.h"
#include "particella.h"

class elettrone : public particella{
public:
    // costruttori
    elettrone(): particella{9.1093826e-31, -1.60217653e-19} {};

    //
    ~elettrone() {};
    // metodi
    virtual void Print() const override { fmt::println("Elettrone =  Massa: {}, Carica: {}", m_massa, m_carica);}

};

//posso provare a includere nello stesso file la classe elettrone e quella particella in modo da non aver troppi file nello stesso progetto 

