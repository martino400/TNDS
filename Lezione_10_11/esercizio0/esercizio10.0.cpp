#pragma once
#include "RandomGen.h"
#include "gplot++.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    // distribuzione uniforme tra 5 10;
    Gnuplot histo{};
    histo.redirect_to_png("Immagini0/Istogramma.png", "1200,900");
    histo.multiplot(2, 2, "Distribuzioni");

    const int M = 100000;
    RandomGen generatore(1);
    vector<double> random;
    for (int i = 0; i < M; i++)
    {
        random.push_back(generatore.Unif(5, 10));
    }
    histo.histogram(random, 200, "Distribuzione uniforme tra 5 e 10");
    histo.set_xlabel("Valori");
    histo.set_xrange(4, 11);
    histo.set_yrange(0, NAN);
    histo.set_ylabel("Densità probabilità");
    histo.show();
    random.clear();

    // distribuzione esponenziale tra 0 e infinito
    generatore.SetSEED(1);
    for (int i = 0; i < M; i++)
    {
        random.push_back(generatore.Exp(1));
    }
    histo.histogram(random, 200, "Distribuzione uniforme esponenziale tra 0 e infinito");
    histo.set_xlabel("Valori");
    histo.set_xrange(0, 8);
    histo.set_yrange(0, NAN);
    histo.set_ylabel("Densità probabilità");
    histo.show();
    random.clear();

    // distribuzione gaussiana centrata in 1 e larghezza 1 con il metodo di Box-Muller.
    generatore.SetSEED(1);
    for (int i = 0; i < M; i++)
    {
        random.push_back(generatore.GaussBOXMULLER(1, 1));
    }
    histo.histogram(random, 200, "Distribuzione gaussiana centrata in 1 e larghezza 1 con il metodo di Box-Muller");
    histo.set_xlabel("Valori");
    histo.set_yrange(0, 2000);
    histo.set_ylabel("Densità probabilità");
    histo.show();
    random.clear();

    // distribuzione gaussiana centrata in 1 e larghezza 1 con il metodo accept-reject
    generatore.SetSEED(1);
    for (int i = 0; i < M; i++)
    {
        random.push_back(generatore.GaussTE(1, 1));
    }
    histo.histogram(random, 200, "Distribuzione gaussiana centrata in 1 e larghezza 1 con il metodo Accept-Reject");
    histo.set_xlabel("Valori");
    histo.set_yrange(0, 2000);
    histo.set_ylabel("Densità probabilità");
    histo.show();
    random.clear();
    return 0;
}
