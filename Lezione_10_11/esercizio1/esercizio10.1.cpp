#pragma once
#include "RandomGen.h"
#include <iostream>
#include <cmath>
#include "gplot++.h"
#include "fmtlib.h"
#include <vector>

using namespace std;

void somme(int M, RandomGen &random, int k, vector<double> &somma, double &per_media);

double varianza(int ndata, vector<double> data, double media);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Bisogna mettere <eseguibile> e <numero di istogrammi> " << endl;
        exit(1);
    }
    int num_tot = stoi(argv[1]);
    const int M = 100000;
    RandomGen random(1);
    // istogrammi
    Gnuplot histo{};
    histo.redirect_to_png("Immagini1/Istogrammasomme.png", "1200,900");
    histo.multiplot(4, 3);
    // Varianza
    Gnuplot vari{};
    vari.redirect_to_png("Immagini1/Varianze.png", "1200,900");
    int k = 1;
    for (k = 1; k <= num_tot; k++)
    {
        double media = 0.0;
        random.SetSEED(1);
        vector<double> somma;
        somme(M, random, k, somma, media);
        histo.histogram(somma, 100, "Histo");
        histo.set_yrange(0, NAN);
        histo.set_xlabel("Valori");
        histo.set_ylabel("Ripetizioni");
        histo.show();
        vari.set_title("Varianza");
        vari.add_point(k, varianza(M, somma, double(media / M)));
        fmt::println("x = {}    y = {}", k, varianza(M, somma, double(media / M))/k);
    }
    vari.plot("Varianze", Gnuplot::LineStyle::LINESPOINTS);
    vari.show();

    return 0;
}

double varianza(int ndata, vector<double> data, double media)
{
    double varianza = 0.0;
    for (int k = 0; k < ndata; k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = varianza / double(ndata);
    return varianza;
}

void somme(int M, RandomGen &random, int k, vector<double> &somma, double &per_media)
{
    // riempimento delle 100000 somme
    for (int t = 0; t < M; t++)
    {
        double sum = 0.0;
        // calcolo somme e riempimento vettore
        for (int i = 1; i <= k; i++)
        {
            sum += random.Rand();
        }
        per_media += sum;
        somma.push_back(sum);
    }
}