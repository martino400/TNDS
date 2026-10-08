#include "funzioni.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    vector<double> vuoto1{10}; //(parentesi graffe) inizializza il vettore aggiungendo un elemento di valore 10.
    cout << vuoto1[0] << "\n";
    vector<double> vuoto2(10); //(parentesi tonde) inizializza il vettore riservando spazio per 10 elementi.
    cout << vuoto2[0]<< "\n";

    if (argc < 3)
    {
        cerr << "Uso del programma: " << argv[0] << " <n_data> <filename>\n";
        return 1;

        // questo serve per segnalare l'errore che passo meno di 3 parametri
    }

    int ndata = stoi(argv[1]); // stoi mi fa diventare argv[1] un intero che inserisco nella variabile ndata
    

    const char *filename = argv[2];

    vector <double> data{Read<double>(ndata, filename)};

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
}
