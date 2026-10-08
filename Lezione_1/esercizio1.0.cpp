#include <fstream>
#include <iostream>
#include <string>
// argc si becca il numero di parametri passati dalla linea di comando
// argv si becca i parametri passati dalla linea di comando
// il primo parametro è sempre il nome dell'eseguibile
using namespace std;
#include "funzioni.h"
// Scriviamo un unico codice che legge i dati da file, li immagazzina in un array dinamico, e infine calcola la media, la varianza e la mediana dei dati raccolti

// per compilare --> g++ esercizio1.0.cpp  -Wall -o main
int main(int argc, char *argv[])
{

    const double g = 9.8;


    int ndata = stoi(argv[1]); // stoi mi fa diventare argv[1] un intero che inserisco nella variabile ndata
    double *data = new double[ndata];

    const char *filename = argv[2];

    // leggo i dati dal file e li carico

    ifstream in(filename);

    if (!in)
    {
        cerr << "Non riesco ad aprire il file " << filename << endl;
        exit(1);
        // verificato, funziona se si mette 1942.txt
    }
    else
    {
        for (int i = 0; i < ndata; i++)
        {
            in >> data[i];
            if (in.eof())
            {
                cout << "Raggiunta la fine del file prima di aver letto " << ndata << "dati" << endl;
            }
        }
    }


    for(int i=0; i<ndata; i++)
    {
        cout << data[i] << endl;
    }
    

    // calcolo media

    double media = 0;

    for (int i = 0; i < ndata; i++)
    {
        media += data[i];
    }

    media /= ndata;
    cout << "La media è = " << media << endl;

    // calcolo varianza

    double varianza1 = 0;

    for (int i = 0; i < ndata; i++)
    {
        varianza1 += pow(data[i] - media, 2);
    }

    varianza1 /= ndata;

    cout << "La varianza è = " << varianza1 << endl;

    // selection sort
    double *ordinato = new double[ndata];

    for (int i = 0; i < ndata; i++)
    {
        ordinato[i] = data[i];
    }
    int pos_min= 0;
    double minimo = ordinato[pos_min];
    for(int j=0; j<ndata; j++)
    {
        pos_min = j;
        minimo = ordinato[pos_min];
        for(int i=j+1; i<ndata; i++)
        {
            if(ordinato[i]<minimo)
            {
                minimo=ordinato[i];
                pos_min = i;
            }
        }

        //scambia
        double c = ordinato[j];
        ordinato[j]= ordinato[pos_min];
        ordinato[pos_min]= c;
    }

    // calcolo mediana
    int numero = 0;
    double mediana = 0;
    if (ndata % 2 == 0)
    {
        numero = ndata / 2;
        mediana = (ordinato[ndata / 2 - 1] + ordinato[ndata / 2]) / 2;
    }
    else
    {
        mediana = (ordinato[ndata/2]);
    }
    cout << "La mediana è = "<< mediana << endl;

    //output su file

    ofstream out("output.txt");
    for(int i=0; i<ndata; i++)
    {
        out << ordinato[i] << endl;
    }
    out.close();
    in.close();

    delete[] ordinato;
    delete[] data;
}


// faccio bene la mediana