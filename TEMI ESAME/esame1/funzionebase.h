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

class integral
{
public:
    integral() : m_a{}, m_b{}, m_sign{}, m_h{} {};
    double integrate(double a, double b, int nstep, funzionebase &f)
    {
        checkInterval(a, b);
        return m_sign * calculate(nstep, f);
    }

    double int_prec(double a, double b, double precisione, funzionebase &f)
    {
        checkInterval(a, b);
        return m_sign * integrate_prec(precisione, f);
    }

    double getA() { return m_a; }
    double getB() { return m_b; }
    double getsign() { return m_sign; }
    double getH() { return m_h; }
    void setH(double h) {m_h = h;}

protected:
    virtual double calculate(int step, const funzionebase &f) = 0;
    virtual double integrate_prec(double prec, const funzionebase &f) = 0;
    void checkInterval(double a, double b)
    {
        m_a = std::min(a, b);
        m_b = std::max(a, b);
        if (b > a)
        {
            m_sign = 1.0;
        }
        else if (b < a)
        {
            m_sign = -1.0;
        }
    }

    double m_a, m_b;
    double m_sign;
    double m_h;
};


class trapezio : public integral
{
public:
    trapezio() : integral() {};

protected:
    double calculate(int nstep, const funzionebase &f) override
    {
        double m_h = (m_b - m_a) / nstep;
        setH(m_h);
        double a{m_a};
        double somma1{f.eval(m_a)+f.eval(m_b)},sum{somma1};;
        for (int i = 0; i <= nstep; i++)
        {
            if(i!= 0 || i!=nstep)
            {
                sum += (f.eval(a));
            }
            a = (m_a + i * m_h);
        }
        return sum * m_h;
    }
    double integrate_prec(double prec, const funzionebase &f) override
    {
        double sc{}, pr{1};
        int n{2};
        do
        {
            sc = pr; //in questo modo non devo calcolare 2 integrali diversi. 
            pr = calculate(n/2, f);
            n*=2;
        } while (prec<fabs(sc-pr)*(4.0)/(3.0));
        //fmt::println("Numero di iterazioni ={}", n);
        return sc;
    }
};



//CALCOLA LA FUNZIONE INTEGRANDA 
class funzione : public funzionebase
{
public:
    funzione(double d, double lambda, double L, double x)
    {
        m_d = d;
        m_lambda = lambda;
        m_L = L;
        m_x = x;
    };

    virtual double eval(double t) const override
    {
        double integranda = (1.0 / m_d) * cos((1.0 / m_lambda) * (sqrt(m_L * m_L + pow(m_x - t, 2)) - sqrt(m_L * m_L + m_x * m_x)));
        return integranda;
    }
    ~funzione() {};

protected:
    double m_d, m_lambda, m_L, m_x;
};



//CALCOLA FUNZIONE INTEGRALE
class func : public funzionebase
{
public:
    func(double d, double lambda, double L, double x)
    {
        m_d = d;
        m_lambda = lambda;
        m_L = L;
        m_x = x;
    };

    func(double d, double lambda, double L)
    {
        m_d = d;
        m_lambda = lambda;
        m_L = L;
    };

    virtual double eval(double x) const override
    {
        trapezio trap;
        funzione f(m_d, m_lambda, m_L, x);
        return trap.int_prec(-m_d / 2.0, m_d / 2.0, 5e-5, f);
    }
    ~func() {};

protected:
    double m_d, m_lambda, m_L, m_x;
};




