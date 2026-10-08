#pragma once
#include <iostream>
#include <cmath>
#include "fmtlib.h"
#include "particella.h"

class elettrone : public particella{
public:
    // costruttori
    elettrone(): particella{9.1093826e-31, -1.60217653e-19} {};

    // distruttore
    ~elettrone();

    // metodi

    void Print() const { fmt::println("Elettrone =  Massa: {}, Carica: {}", m_massa, m_carica);}

};



