#pragma once
#include <iostream>
#include <cmath>
#include "RandomGen.h"
#include "funzionebase.h"

using namespace std;
double varianza(int ndata, vector<double> data, double media);
class IntegralMC
{
public:
    IntegralMC(unsigned int seed) : random(seed)
    {
        m_punti = 0.0;
        errore = 0.0;
    }
    virtual double valore(const funzionebase &f, double max, double min, double fmax, unsigned int punti) = 0;

    double GetErrore() const { return errore; }
    int GetN() const { return m_punti; }

protected:
    unsigned int m_punti;
    RandomGen random;
    double errore;
};

class IntegraMedia : public IntegralMC
{
public:
    IntegraMedia(unsigned int seed) : IntegralMC(seed) {}
    double valore(const funzionebase &f, double min, double max, double fmax, unsigned int punti)
    {
        m_punti = punti;
        double delta = max - min, somma{};
        vector <double> err;
        for (int i = 0; i < punti; i++)
        {
            // mi da un numero sulle x causale compreso tra min e max e poi ne trova le immagini
            somma += f.eval(random.Unif(min, max));
            err.push_back(f.eval(random.Unif(min, max)));
        }
        errore = sqrt(varianza(m_punti, err, double(somma/m_punti)));
        delta = double(delta * somma / punti);
        return delta;
    }
};

class IntegraHitMiss : public IntegralMC
{
public:
    IntegraHitMiss(unsigned int seed) : IntegralMC(seed) { ; }
    double valore(const funzionebase &f, double min, double max, double fmax, unsigned int punti)
    {
        m_punti = punti;
        double delta = max - min;
        double y{}, x{};
        double valore{};
        int nhit{}, ntot{};
        for (int i = 0; i < m_punti; i++)
        {
            y = random.Unif(0.0, fmax);
            x = random.Unif(min, max);
            if (y < f.eval(x))
            {
                nhit++;
            }
            ntot++;
            y = 0.0, x = 0.0;
        }
        valore = double(delta*fmax* nhit/ntot);
        return valore;
    }

};


double varianza(int ndata, vector<double> data, double media)
{
    double varianza = 0;
    for (int k = 0; k < ndata; k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = varianza / double(ndata);
    return varianza;
}
