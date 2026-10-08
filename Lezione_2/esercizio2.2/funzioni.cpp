#include "funzioni.h"

double media(const Vettore& v)
{
    double media = 0;

    for (int i = 0; i < v.GetN(); i++)
    {
        media += v[i];
    }
    return media /= double(v.GetN());
}


double varianza(const Vettore& data, double media)
{
    double varianza = 0;
    int ndata = data.GetN();
    for (int k = 0; k < ndata; k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = varianza / double(ndata);
    return varianza;
}
 //selection sort: prendo in ingresso due Vettori e li ordino come diceva la scorsa lezione, ordina CRESCENTE
void ordina(Vettore& ordinato)
{

    int pos_min = 0;
    double minimo = ordinato[pos_min];
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
        double c = ordinato[j];
        ordinato[j] = ordinato[pos_min];
        ordinato[pos_min] = c;
    }
}

double mediana(Vettore a)
{
    //ordino qua in modo che sul file non viene ordinato ma viene ordinato 
    //quello copiato nella funzione
    ordina(a);
    int ndata = a.GetN();
    double mediana = 0;
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

void Print(const Vettore& data) 
{
    for (int i = 0; i < data.GetN(); i++)
    {
        cout << setw(5) << " giorno " << i + 1 << setw(5) << "" << data[i] << endl;
    }
}

void Print(const Vettore& data, const char *filename) 
{
    ofstream out(filename);
    for (int i = 0; i < data.GetN(); i++)
    {
        out << setw(5) << " giorno " << i + 1 << setw(5) << "" << data[i] << endl;
    }
    out.close();
}

Vettore Read(int ndata, const char* filename)
{
    Vettore data(ndata);
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