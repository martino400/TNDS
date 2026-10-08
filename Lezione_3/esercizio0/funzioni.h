#include <fstream>
#include <iostream>
#include <string>
#include "Vettore.h"


// argc si becca il numero di parametri passati dalla linea di comando
// argv si becca i parametri passati dalla linea di comando
// il primo parametro è sempre il nome dell'eseguibile

//IMPLEMENTAZIONE 
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

//Leggo file
template <typename T> Vettore<T> Read(int ndata, const char *filename);
//Media vettore, prendo reference in modo da non fare una copia dei dati sulla funzione e allo stesso tempo const mi permette che non vengano modificati
template <typename T> T media(const Vettore<T> &v);
//Mediana vettore
template <typename T> T mediana(Vettore<T> a);
//Varianza vettore
template <typename T> T varianza(const Vettore<T> &a, double media);
//Selection sort
template <typename T> void ordina(Vettore<T>& ordino);
// stampa a video
template <typename T> void Print(const Vettore<T>& data);
// stampa su file
template <typename T> void Print(const Vettore<T>& data, const char *filename);




//IMPLEMENTAZIONE 
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T> T media(const Vettore<T>& v)
{
    T media = 0;

    for (int i = 0; i < v.GetN(); i++)
    {
        media += v[i];
    }

    media /= v.GetN();
    return media;
}


template <typename T> T varianza(const Vettore<T> &data, double media)
{
    T varianza = 0;
    int ndata = data.GetN();
    for (int k = 0; k < ndata; k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = varianza / double(ndata);
    return varianza;
}
 //selection sort: prendo in ingresso due Vettori e li ordino come diceva la scorsa lezione, ordina CRESCENTE
template <typename T> void ordina(Vettore<T>& ordinato)
{

    int pos_min = 0;
    T minimo = ordinato[pos_min];
    for (int j = 0; j < ordinato.GetN(); j++)
    {
        pos_min = j;
        minimo = ordinato[pos_min];
        for (int i = j + 1; i < ordinato.GetN(); i++)
        {
            if (ordinato[i] < minimo)
            {
                minimo = ordinato[i];
                pos_min = i;
            }
        }
        // Scambia l'elemento corrente con l'elemento minimo trovato
        T c = ordinato[j];
        ordinato[j] = ordinato[pos_min];
        ordinato[pos_min] = c;
    }
}

template <typename T> T mediana(Vettore<T> a)
{
    //ordino qua in modo che sul file non viene ordinato ma viene ordinato 
    //quello copiato nella funzione
    ordina(a);
    int ndata = a.GetN();
    T mediana = 0;
    if (ndata % 2 == 0)
    {
        mediana = (a[ ndata/ 2 - 1] + a[ndata / 2]) / 2.;
    }
    else
    {
        mediana = a[ndata / 2];
    }
    return mediana;
}

template <typename T> void Print(const Vettore<T>& data)
{
    for (int i = 0; i < data.GetN(); i++)
    {
        cout << setw(5) << " giorno " << i + 1 << setw(5) << "" << data[i] << endl;
    }
}

template <typename T> void Print(const Vettore<T>& data, const char *filename)
{
    ofstream out(filename);
    for (int i = 0; i < data.GetN(); i++)
    {
        out << setw(5) << " giorno " << i + 1 << setw(5) << "" << data[i] << endl;
    }
    out.close();
}

template <typename T> Vettore<T> Read(int ndata, const char *filename)
{
    Vettore <T> data{ndata};
    ifstream in(filename);
    if (!in)
    {
        cerr << "Non riesco ad aprire il file " << filename << endl;
        exit(1);
        // verificato, funziona se si mette 1942.txt
    }
    else
    {
        for (int k = 0; k < ndata; k++)
        {
            if (in.eof())
            {
                cout << "Raggiunta fine file" << endl;
                exit(33);
            }
            in >> data[k];
        }
    }
    return data;

    in.close();
}


