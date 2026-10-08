#include <fstream>
#include <iostream>
#include <string>
#include <vector>


// argc si becca il numero di parametri passati dalla linea di comando
// argv si becca i parametri passati dalla linea di comando
// il primo parametro è sempre il nome dell'eseguibile

//IMPLEMENTAZIONE 
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

//Leggo file
template <typename T> vector<T> Read(int ndata, const char *filename);
//Media vector, prendo reference in modo da non fare una copia dei dati sulla funzione e allo stesso tempo const mi permette che non vengano modificati
template <typename T> T media(const vector<T> &v);
//Mediana vector
template <typename T> T mediana(vector<T> a);
//Varianza vector
template <typename T> T varianza(const vector<T> &a, double media);
//Selection sort
template <typename T> void ordina(vector<T>& ordino);
// stampa a video
template <typename T> void Print(const vector<T>& data);
// stampa su file
template <typename T> void Print(const vector<T>& data, const char *filename);




//IMPLEMENTAZIONE 
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T> T media(const vector<T>& v)
{
    T media = 0;

    for (int i = 0; i < ssize(v); i++)
    {
        media += v[i];
    }

    media /= ssize(v);
    return media;
}


template <typename T> T varianza(const vector<T> &v, double media)
{
    T varianza = 0;
    int ndata = ssize(v);
    for (int k = 0; k < ndata; k++)
    {
        varianza += (v[k] - media) * (v[k] - media);
    }

    varianza = varianza / (double(ndata)-1.0);
    return varianza;
}
 //selection sort: prendo in ingresso due Vettori e li ordino come diceva la scorsa lezione, ordina CRESCENTE
template <typename T> void ordina(vector<T>& v)
{

    int pos_min = 0;
    T minimo = v[pos_min];
    for (int j = 0; j < ssize(v); j++)
    {
        pos_min = j;
        minimo = v[pos_min];
        for (int i = j + 1; i < ssize(v); i++)
        {
            if (v[i] < minimo)
            {
                minimo = v[i];
                pos_min = i;
            }
        }
        // Scambia l'elemento corrente con l'elemento minimo trovato
        T c = v[j];
        v[j] = v[pos_min];
        v[pos_min] = c;
    }
}

template <typename T> T mediana(vector<T> v)
{
    //ordino qua in modo che sul file non viene ordinato ma viene ordinato 
    //quello copiato nella funzione
    sort(v.begin(), v.end());
    int ndata = ssize(v);
    T mediana = 0;
    if (ndata % 2 == 0)
    {
        mediana = (v[ ndata/ 2 - 1] + v[ndata / 2]) / 2.;
    }
    else
    {
        mediana = v[ndata / 2];
    }
    return mediana;
}

template <typename T> void Print(const vector<T>& v)
{
    for (int i = 0; i < ssize(v); i++)
    {
        cout << setw(5) << " giorno " << i + 1 << setw(5) << "" << v[i] << endl;
    }
}

template <typename T> void Print(const vector<T>& v, const char *filename)
{
    ofstream out(filename);
    for (int i = 0; i < ssize(v); i++)
    {
        out << setw(5) << " giorno " << i + 1 << setw(5) << "" << v[i] << endl;
    }
    out.close();
}

template <typename T> vector<T> Read(int ndata, const char *filename)
{
    vector <T> data;
    ifstream in(filename);
    if (!in)
    {
        cerr << "Non riesco ad aprire il file " << filename << endl;
        exit(1);
        // verificato, funziona se si mette 1942.txt
    }
    else
    {
        while(!in.eof())
        {
            T val;
            in >> val;
            //aggiunge un nuovo elemento alla fine del vettore
            data.push_back(val); 
        }
    }
    return data;

    in.close();
}


