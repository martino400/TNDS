#pragma once
#include <iostream>
#include <cmath>
#include "funzionebase.h"

using namespace std;

class solutore
{
public:
    solutore() {};
    solutore(double prec);
    virtual ~solutore() {};
    virtual double CercaZeriReference(double xmin, double xmax, const funzionebase &f, int nmax, double precisione) = 0;
    void setPrecisione(double epsilon) { m_prec = epsilon; }
    void setNMAXiterazioni(int iter) { m_nmax = iter; }
    int getNMAXiterazioni() { return m_nmax; }
    int getNITERAZIONI() { return m_niterations; }
    double getPrec() { return m_prec; }
    bool getFound() { return m_found; }

protected:
    double m_a, m_b;     // range of the interval to explore
    double m_prec;       // precision of the solution
    int m_nmax;          // Maximum number of iterations
    int m_niterations;   // Actual number of iterations
    bool m_found = true; // mi dice se ho sgravato con il numero di iterazioni, se falso allora TROPPE
};

class bisezione : public solutore
{
public:
    bisezione() {};
    virtual ~bisezione() {};
    virtual double CercaZeriReference(double xmin, double xmax, const funzionebase &f, int nmax, double precisione); //passa la funzione by reference
};

double bisezione::CercaZeriReference(double xmin, double xmax, const funzionebase &f, int nmax, double precisione)
{
    m_a = xmin;
    m_b = xmax;
    m_prec = precisione;
    m_nmax = nmax;
    long double delta = abs(xmax - xmin);
    double medio;
    double segn_a, segn_medio, segn_b;
    int i=0;
    while (delta >= m_prec && i<nmax)
    {
        i++;
        if (f.eval(xmax) == 0) 
            return xmax;
        if (f.eval(xmin) == 0)
            return xmin;
        delta = abs(xmax - xmin);
        medio = xmin + (xmax - xmin) / 2;
        Segno sg1, sg2, sg3;
        segn_a = sg1.eval((f.eval(xmin)));
        segn_medio = sg2.eval((f.eval(medio)));
        segn_b = sg3.eval((f.eval(xmax)));
        if (f.eval(medio) == 0)
        {
            return medio;
        }
        else if (segn_a * segn_medio < 0)
        {
            xmax = medio;
        }
        else if (segn_medio * segn_b < 0)
        {
            xmin = medio;
        }
    }
    if (i >= nmax)
    {
        m_found = false;
        cerr << "Troppe iterazioni rispetto a <nmaxCICLI> specificato" << endl;
    }
    m_niterations = i;
    return medio;
}
