#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <cassert>
#include "fmtlib.h"
#include "gplot++.h"
#include "RandomGen.h"
#include "funzionebase.h"
#include "IntegralMC.h"
#include <fstream>
#include <string>

using namespace std;
using namespace fmt;

void MissAndMedia(vector<double> integrali, double data, Gnuplot histo, vector<double> &var, vector<double> &varHitMiss);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Devi inserire <eseguibile> e <precisione>" << endl;
        exit(1);
    }
    vector<int> num_of_points{100, 500, 1000, 5000, 10000, 50000, 100000};

    double precisione = (stod(argv[1]) * stod(argv[1]));

    vector<double> integrali;
    vector<double> var;
    vector<double> varHitMiss;

    Gnuplot histo{};
    histo.redirect_to_png("Dati10.2/IstogrammiMediaandHitMiss.png", "1500, 1700");
    histo.multiplot(7, 2);

    double data{};

    MissAndMedia(integrali, data, histo, var, varHitMiss);

    // scelgo arbitrariamente una N per cui trovare k tanto è uguale per tutti, mi determina l'andamento
    //  generale dell'errore
    double k_andamento_err = num_of_points[2] * var[2];

    double k_andamento = num_of_points[2] * varHitMiss[2];

    int Ntilda = k_andamento_err / precisione;

    int N_necessario = k_andamento / precisione;

    // in questo modo non rilevo un integrale con una precisione di x
    // ma trovo un integrale che appartiene alla gaussiana con precisione x
    // vuol dire che è anche possibile che stia alle code
    // però più prendo sigma stretto più è improbabile che stia alle code

    fmt::println("N iterazioni per avere una gaussiana con sigma {} = {}", precisione, N_necessario);

    fmt::println("Importante capire che non è detto che qualsiasi integrale io calcoli con {} punti, starà dentro \n la pancia della gaussiana di almeno {}, non vuol dire questo, \n vuol dire quante iterazioni devo fare almeno per avere una gaussiana con sigma di {}", Ntilda, sqrt(precisione), sqrt(precisione));
    return 0;
}

void MissAndMedia(vector<double> integrali, double data, Gnuplot histo, vector<double> &var, vector<double> &varHitMiss)
{
    vector<int> num_of_points{100, 500, 1000, 5000, 10000, 50000, 100000};

    for (int i = 0; i < num_of_points.size(); i++)
    {
        double somma{};
        int conta{};
        ifstream in;
        in.open(fmt::format("Dati10.2/RisultatiIntegraliMedia{}.dat", i + 1));
        integrali.clear();
        while (!in.eof())
        {
            in >> data;
            integrali.push_back(data);
            somma += data;
            conta++;
        }
        //var.push_back(varianza(conta, integrali, double(somma / conta)));
        histo.histogram(integrali, 40, fmt::format("IstogrammaIntegraleMedia"), Gnuplot::LineStyle::BOXES);
        histo.set_xlabel("Valore Integrale x*sinx");
        histo.set_ylabel("Quantità valori");
        histo.set_xrange(0.5, 1.5);
        histo.show();
        in.close();
    }

    Gnuplot plt{};
    plt.redirect_to_png(fmt::format("Dati10.2/Varianza.png"));
    plt.plot(num_of_points, var, "", Gnuplot::LineStyle::LINESPOINTS);
    for (int i = 0; i < 7; i++)
    {
        double somma{};
        int conta{};
        ifstream in;
        in.open(fmt::format("Dati10.2/RisultatiIntegraliMiss{}.dat", i + 1));
        integrali.clear();
        while (!in.eof())
        {
            in >> data;
            integrali.push_back(data);
            somma += data;
            conta++;
        }
        varHitMiss.push_back(varianza(conta, integrali, double(somma / conta)));
        histo.histogram(integrali, 40, "IstogrammaIntegraleHitMiss", Gnuplot::LineStyle::BOXES);
        histo.set_xrange(0.5, 1.5);
        histo.set_xlabel("Valore Integrale x*sinx");
        histo.set_ylabel("Quantità valori");
        histo.show();
        in.close();
    }
    plt.plot(num_of_points, varHitMiss, "", Gnuplot::LineStyle::LINESPOINTS);
    plt.set_logscale(Gnuplot::AxisScale::LOGXY);
    plt.set_title("Andamento varianza al crescere di quantità di punti N per l'integrazione");
    plt.set_xrange(70, 130000);
    plt.set_xlabel("Quantità di punti N");
    plt.set_ylabel("Varianza");
    plt.show();

}
