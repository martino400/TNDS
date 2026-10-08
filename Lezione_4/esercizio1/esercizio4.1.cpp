#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "funzioni.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    cout << ("------------------------------------------------ Milikan.cpp ------------------------------------------------------------------------") << endl;
    int ndata = 0;
    ofstream out;
    out.open("output.dat");
    vector<double> v = ParseFile("Milikan.dat");
    double q, somma = 0, dev = 0;
    int i = 0;
    TApplication app{0, 0, 0};

    TCanvas can1{};
    can1.cd();
    can1.SetGridx();
    can1.SetGridy();
    // Questo serve per far vedere come sono distribuite le cariche
    TH1F histo{"cariche", "Distribuzione delle cariche", 30, 2e-19, 16e-19};
    for (int i{}; i < ssize(v); i++)
    {
        cout << v[i] << endl;
        histo.Fill(v[i]);
    }
    histo.Draw();
    histo.GetXaxis()->SetTitle("Charge [C]");
    can1.SaveAs("Immagini/distribuzione.png");

    TGraphErrors trend;
    double min, err;

    // Questo serve per tirare fuori un grafico di S(q)

    // il valore massimo che un double può assumere in c++
    double sqmin = {DBL_MAX};
    double crescita = 0.001e-19;

    for (q = 1.0e-19; q < 1.9e-19; q += crescita, i++)
    {
        somma = (funzione(q, v));
        dev = deriv(q, v);
        trend.SetPoint(i, q, somma);
        if (funzione(q, v) < sqmin)
        {
            sqmin = funzione(q, v);
            min = dev;
            err = sqrt(sqmin) / (sqrt(ssize(v)) * (sqrt(ssize(v)) - 1)); // deviazione standard della media, errore sulla carica dell'elettrone trovata
        }
        // trend.SetPointError(i, 0); //Errore, che ha come primo elemento l'elemento i-esimo a cui è assegnato, secondo elemento il valore dell'errore sulle x, terzo elemento il valore dell'errore sulle y
    }
    double const epslion = 1.e-39;
    double count = 0;
    for (q = 1.0e-19; q < 1.9e-19; q += crescita, i++)
    {
        if ((funzione(sqmin, v) - funzione(q, v)) < epslion)
        {
            count++;
        }
        // trend.SetPointError(i, 0); //Errore, che ha come primo elemento l'elemento i-esimo a cui è assegnato, secondo elemento il valore dell'errore sulle x, terzo elemento il valore dell'errore sulle y
    }
    count = count * crescita;

    cout << "Il valore della carica minimo = " << min << "  ±  " << count << endl;
    cout << "Errore percentuale sulla misura rispetto al valore vero e proprio = " << abs(100 - (min / 1.602e-19) * 100) << "%" << endl;

    TCanvas c{"S(q)", "S(q)"};

    c.cd();
    c.SetGridx();
    c.SetGridy();

    trend.SetMarkerSize(1);
    trend.SetMarkerStyle(1);
    trend.SetFillColor(5);

    trend.SetTitle("S(q)");
    trend.GetXaxis()->SetTitle("q di prova");
    trend.GetYaxis()->SetTitle("Valori S(q)");
    trend.Draw();
    trend.Draw("pX");

    c.SaveAs("Immagini/plotS(q).jpeg");
    out.close();

    app.Run();
}
