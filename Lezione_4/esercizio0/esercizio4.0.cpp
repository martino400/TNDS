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
  test_statistics_with_stride();
  cout << ("------------------------------------------------Esercizio 4.0.cpp ----------------------------------------------------------") << endl;
  int ndata = 0;
  double delta, errore;
  ofstream out;
  out.open("output.dat");

  TApplication app{"app", 0, 0};

  // oggetto per rappresentare un andamento x (anno) verso y (delta medio)
  TGraphErrors trend;

  for (int year{1941}, index{}; year < 2024; year++, index++)
  {
    string filename{format("TemperatureMilano/{}.txt", year)};
    vector<double> data{Read<double>(ndata, filename)};
    delta = mean(data, 7);
    errore = stddev(data, 7);

    trend.SetPoint(index, year, delta);//METTE IL PUNTO SUL GRAFICO
    trend.SetPointError(index, 0, errore);//METTE L'ERRORE SUL GRAFICO

    cout << format("Anno {} Δ medio = {:.3f} ± {:.3f}\n", year, delta, errore);
    out << format("Anno {} Δ medio = {:.3f} ± {:.3f}", year, delta, errore) << endl;
  }
  

  TCanvas c{"Temperature trend","Temperature trend"};
  c.cd();
  c.SetGridx();
  c.SetGridy();

  trend.SetMarkerSize(0.5);
  trend.SetMarkerStyle(20);
  trend.SetFillColor(5);

  trend.SetTitle("Temperature trend");
  trend.GetXaxis()->SetTitle("Anno");
  trend.GetYaxis()->SetTitle("#Delta (#circ C)");
  trend.Draw();
  trend.Draw("pX");

  c.SaveAs("Immagini/trend.png");

  app.Run();
  out.close();
}

