#pragma once
#include <iostream>
#include "fmtlib.h"
#include <cmath>


// classe FUNZIONEBASE

class funzionebase
{
public:
    virtual double eval(double x) const = 0;
    virtual ~funzionebase() {};
};

// classe FIGLIA PARABOLA

class parabola : public funzionebase
{
public:
    parabola() : m_a{}, m_b{}, m_c{1.0} {};
    parabola(double a, double b, double c) : m_a{a}, m_b{b}, m_c{c} {};

    virtual double eval(double x) const override
    {
        return (m_a * x + m_b) * x + m_c; // metodo di horner (da capire)
    }
    ~parabola() {};

    void setA(double a) { m_a = a; }
    void setB(double b) { m_b = b; }
    void setC(double c) { m_c = c; }

    double GetA() const { return m_a; }
    double GetB() const { return m_b; }
    double GetC() const { return m_c; }

    double GetVertex() const { return (-m_b) / (2 * m_a); }

private:
    double m_a, m_b, m_c;
};

class sincos : public funzionebase
{
public:
    sincos(double a, double b) : m_a{a}, m_b{b} {};
    // faccio una funzione molto generica fatta in questo modo a*x*cos(b*x) - sin(b*x)=0

    virtual double eval(double x) const override
    {
        return sin(m_b * x) - (m_a * x * cos(m_b * x));
    }
    ~sincos() {};

    void setA(double a) { m_a = a; }
    void setB(double b) { m_b = b; }
    double GetA() const { return m_a; }
    double GetB() const { return m_b; }

private:
    double m_a, m_b;
};

class Segno : public funzionebase
{
public:
    virtual double eval(double x) const override
    {
        if (x == 0)
        {
            return 0.0;
        }
        else if (x > 0)
        {
            return 1.0;
        }
        else if (x < 0)
        {
            return -1.0;
        }
    }
};

class xsinx : public funzionebase
{
public:
    xsinx() {};
    // faccio una funzione molto generica fatta in questo modo a*x*cos(b*x) - sin(b*x)=0

    virtual double eval(double x) const override
    {
        return x * sin(x);
    }
    ~xsinx() {};
};

class sinx : public funzionebase
{
public:
    sinx() {};
    // faccio una funzione molto generica fatta in questo modo a*x*cos(b*x) - sin(b*x)=0

    virtual double eval(double x) const override
    {
        return  sin(x);
    }
    ~sinx() {};
};



class f_x : public funzionebase
{
public:
    f_x() {};

    virtual double eval(double x) const override{
        return x*x*x*log(sqrt(e + x*x));
    }
    ~f_x() {};
private:
    const double e = 2.71828182845904523536;

};

class f_x2 : public funzionebase
{
public:
    f_x2() {};

    virtual double eval(double x) const override{
        return 1/(sqrt(4 - x*x));
    }
    ~f_x2() {};

};






