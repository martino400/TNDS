#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "funzioni.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  // Stessi test dell'esercizio 3.1, ma qui adattateli per std::vector
  if (argc < 3)
  {
    cerr << "Uso del programma: " << argv[0] << " <n_data> <filename>\n";
    return 1;
  }
  vector<double> vuoto1{10}; //(parentesi graffe) inizializza il vettore aggiungendo un elemento di valore 10.
  cout << vuoto1[0] << "\n";
  vector<double> vuoto2(10); //(parentesi tonde) inizializza il vettore riservando spazio per 10 elementi.
  cout << vuoto2[0] << "\n";

  int ndata = stoi(argv[1]); // stoi mi fa diventare argv[1] un intero che inserisco nella variabile ndata

  const char *filename = argv[2];

  vector<double> data{Read<double>(ndata, filename)};

  // leggo i dati dal file e li carico, utilizzo di MOVE
  // calcolo media
  double average = media(data);
  cout << "La media = " << average << endl;
  // calcolo varianza
  double varianza1 = varianza(data, average);
  cout << "La varianza è = " << varianza1 << endl;
  // calcolo mediana
  double mediana1 = 0;
  mediana1 = mediana(data);
  cout << "La mediana è = " << mediana1 << endl;

  Print(data);
  Print(data, "output.txt"); // stampa su file
  // creo un processo "app" che lascia il programma attivo ( app.Run() ) in modo
  // da permettermi di vedere gli outputs grafici

  TApplication app{"app", 0, 0};

  // L'opzione StatOverflows permette di calcolalare
  //  le informazioni statistiche anche se il dato sta fuori dal range di definizione
  //  dell'istogramma

  TH1F histo{"Dati", "Numero di dati entro un Delta di Temperatura", 60, -10, 10};
  histo.StatOverflows(true);

  for (int k{}; k < data.size(); k++)
  {
    histo.Fill(data[k]);
  }

  // accedo a informazioni statistiche
  cout << "Media dei valori caricati = " << histo.GetMean() << endl;
  //media fatta da vector
  cout << "Media dei valori caricati = " << media(data) << endl;

  // disegno
  TCanvas mycanvas{"Histo", "Histo"};

  histo.Draw();
  histo.GetXaxis()->SetTitle("measurement");
  
mycanvas.Update(); // Aggiorna il canvas
histo.SaveAs("Immagini/DistribuzioneDelta.root");

  app.Run();

}
