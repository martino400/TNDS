#pragma once
#include <iostream>
#include <cmath>

class posizione
{
public:
    // costruttori
    posizione();
    posizione(double x, double y, double z);

    // distruttore
    ~posizione();

    // metodi
    double getX() const; // Coordinate cartesiane
    double getY() const;
    double getZ() const;
    double getR() const; // Coordinate sferiche
    double getPhi() const;
    double getTheta() const; // Coordinate cilindriche
    double getRho() const;
    double Distanza(const posizione &a) const; // distanza da un altro punto

protected:
    double m_x;
    double m_y;
    double m_z;
};

posizione::posizione() : m_x{}, m_y{}, m_z{} {}

posizione::posizione(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z} {}

posizione::~posizione() {}

double posizione::getX() const { return m_x; }


double posizione::getY() const{ return m_y; }


double posizione::getZ()const { return m_z; }


double posizione::getR() const { return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2)); }

// angolo sul piano x-y
double posizione::getPhi() const {return atan2(m_y, m_x);} 
// angolo azimutale (sale e scende)
double posizione::getTheta() const { return acos(m_z / getR()); } 

double posizione::getRho() const { return getR() * sin(getTheta()); } 

double posizione::Distanza(const posizione& a) const
{
    return sqrt(pow(m_x - a.getX(), 2) + pow(m_y - a.getY(), 2) + pow(m_z - a.getZ(), 2));
}
