#pragma once
#include <iostream>
#include <cmath>
#include <vector>

class RandomGen
{
private:
    unsigned int m_a = 1664525, m_c = 1013904223, m_m = pow(2, 31);
    unsigned int seed;

public:
    RandomGen(unsigned int a) { seed = a; };
    void SetA(unsigned int a) { m_a = a; }
    void SetC(unsigned int a) { m_c = a; }
    void SetM(unsigned int a) { m_m = a; }
    void SetSEED(unsigned int a) { seed = a; }

    // random tra 0 e 1
    double Rand()
    {
        double casuale = (m_a * seed + m_c) %m_m;
        seed = casuale;
        return casuale / m_m;
    }
    // distribuzione uniforme in un intervallo specifico
    double Unif(double xmin, double xmax)
    {
        double random = Rand();
        random = xmin + (xmax - xmin) * random;
        return random;
    }
    // distribuzione gaussiana
    double GaussTE(double mean, double sigma)
    {
        double x{}, y{};
        while (0 < 1)
        {
            x = Unif(-5.0, 5.0);
            y = Rand();
            if (y < exp(-(x) * (x) / 2))
            {
                return (mean + sigma * x);
            }
        }
    }

    double GaussBOXMULLER(double mean, double sigma)
    {
        double s = Rand();
        double t = Rand();
        return mean + sigma*(sqrt(-2.0*log(s))*cos(2*M_PI*t));
    }

    // distribuzione esponenziale
    double Exp(double mean)
    {
        double casuale = Rand();
        // ossia il numero che restituisco è il numero che mi garantisce di avere questo probabilità
        return -(1 / mean) * log(1 - casuale);
    }
};
