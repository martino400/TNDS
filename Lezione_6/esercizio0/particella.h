#pragma once
#include <iostream>
#include <cmath>
#include "fmtlib.h"

class particella
{
public:
    // costruttori
    particella();
    particella(double m, double c);

    // distruttore
    ~particella();

    // metodi
    double getMassa() const { return m_massa; }
    double getCarica() const { return m_carica; }

    virtual void Print() const ;

protected:
    double m_massa;
    double m_carica;
};

particella::particella() : m_massa{}, m_carica{} {}

particella::particella(double m, double cz) : m_massa{m}, m_carica{cz} {}

particella::~particella() {}

void particella::Print() const
{
    fmt::println("Particella Massa = {},  Carica = {}", getMassa(), getCarica());
}


