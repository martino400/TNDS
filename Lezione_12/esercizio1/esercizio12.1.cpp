#include <array>
#include <vector>
#include <iostream>
#include <cassert>
#include "fmtlib.h"
#include "gplot++.h"
#include "RandomGen.h"
#include "Esperimento.h"
#include <fstream>
#include <string>

using namespace std;
using namespace fmt;

double media(vector<double> data)
{
    double media{};

    for (int i = 0; i < ssize(data); i++)
    {
        media += data[i];
    }
    double val = double(media / ssize(data));
    return val;
}

void stampafile(ofstream &out, int n_simulazione, double dev, double average, EsperimentoAttrito experiment)
{
    out << "Simulazione N" << n_simulazione << endl;
    out << "Sigma T =" << experiment.getSigmaDeltaT() << " SigmaRagg = " << experiment.getSigmaDeltaRagg() << " SigmaPosizione= " << experiment.getSigmaDeltaX() << endl;
    out << "Deviazione = " << dev << " Media = " << average << endl << endl;
}

bool are_close(double calculated, double expected, double epsilon = 1.0e-7)
{
    return fabs(calculated - expected) < epsilon;
}

void test_media(void)
{
    double average;
    vector<double> eta;
    EsperimentoAttrito experiment(3);
    experiment.setRmisurato(0.01);
    for (int i = 0; i < 1000; i++)
    {
        experiment.esegui();
        experiment.analizza();
        eta.push_back(experiment.getEta());
    }
    average = media(eta);

    assert(are_close(average, 0.830342440314));

    cerr << "Funziona attrito! 🥳\n";
}

double deviazione(vector<double> data, double media)
{
    double varianza = 0;
    for (int k = 0; k < data.size(); k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = double(varianza / data.size());
    return (varianza);
}

void plot(vector<double> dev1, vector<double> dev2, Gnuplot &scatter)
{
    scatter.set_xlabel("Variabile X");
    scatter.set_ylabel("Variabile Y");
    scatter.histogram(dev1, 100);
    scatter.show();
    scatter.histogram(dev1, 100);
    scatter.show();
    scatter.plot(dev1, dev2, "", Gnuplot::LineStyle::POINTS);
    scatter.show();
}

int main(int argc, char *argv[])
{
    // test_media();
    const int N = 1000;
    EsperimentoAttrito experiment(1);

    double dev{}, average{};
    vector<double> eta;
    int n_simulazione = 1;

    ofstream out;
    out.open("Risultati.dat");
    experiment.setRmisurato(0.01);

    for (int i = 0; i < N; i++)
    {
        experiment.esegui();
        experiment.analizza();
        eta.push_back(experiment.getEta());
    }
    dev = sqrt(deviazione(eta, media(eta)));
    average = media(eta);
    stampafile(out, n_simulazione, dev, average, experiment);

    eta.clear();
    n_simulazione++;

    experiment.setSigmaDeltaT(0.0);
    experiment.setSigmaDeltaX(0.0);
    for (int i = 0; i < N; i++)
    {
        experiment.esegui();
        experiment.analizza();
        eta.push_back(experiment.getEta());
    }
    dev = sqrt(deviazione(eta, media(eta)));
    average = media(eta);
    stampafile(out, n_simulazione, dev, average, experiment);

    out.close();

    return 0;
}
