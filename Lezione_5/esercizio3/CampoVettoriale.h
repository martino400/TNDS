#pragma once
#include "posizione.h"
#include <iostream>
#include "fmtlib.h"

class CampoVettoriale : public posizione
{
public:
    // construct
    CampoVettoriale(const posizione &a);
    CampoVettoriale(const posizione &a, double Fx, double Fy, double Fz);
    CampoVettoriale(double x, double y, double z, double Fx, double Fy, double Fz);

    // destroy
    ~CampoVettoriale() {};

    // methods
    CampoVettoriale &operator+=(const CampoVettoriale &a);
    CampoVettoriale operator+(const CampoVettoriale &a) const;

    double getFx() const { return m_Fx; };
    double getFy() const { return m_Fy; };
    double getFz() const { return m_Fz; };

    double Modulo() const;

protected:
    double m_Fx, m_Fy, m_Fz;
};

double CampoVettoriale::Modulo() const { return sqrt(m_Fx * m_Fx + m_Fy * m_Fy + m_Fz * m_Fz); }

CampoVettoriale::CampoVettoriale(const posizione &a) : m_Fx{}, m_Fy{}, m_Fz{} {}

CampoVettoriale::CampoVettoriale(const posizione &a, double Fx, double Fy, double Fz) : m_Fx{Fx}, m_Fy{Fy}, m_Fz{Fz} {}

CampoVettoriale::CampoVettoriale(double x, double y, double z, double Fx, double Fy, double Fz) : m_Fx{Fx}, m_Fy{Fy}, m_Fz{Fz} {}

CampoVettoriale CampoVettoriale::operator+(const CampoVettoriale &a)const
{
    if (a.getX() != getX() || a.getY() != getY() || a.getZ() != getZ())
    {
        fmt::print(stderr,
                   "Somma di campi vettoriali in punti diversi non ammessa\n");
        exit(1);
    }
    CampoVettoriale const sum(a.getX(), a.getY(), a.getZ(), a.getFx()+ getFx(), a.getFy()+getFy(), a.getFz()+getFz());
    return sum;
}

CampoVettoriale &CampoVettoriale::operator+=(const CampoVettoriale &a) {return *this = *this + a; }