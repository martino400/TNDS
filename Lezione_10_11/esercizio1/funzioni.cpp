#include "funzioni.h"

double media(int ndata, double *data)
{
    double media = 0;

    for (int i = 0; i < ndata; i++)
    {
        media += data[i];
    }

    media /= ndata;
    return media;
}

double varianza(int ndata, double *data, double media)
{
    double varianza = 0;
    for (int k = 0; k < ndata; k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = varianza / double(ndata);
    return varianza;
}

void ordina(int ndata, double *data, double *ordinato)
{
    for (int i = 0; i < ndata; i++)
    {
        ordinato[i] = data[i];
    }
    int pos_min = 0;
    double minimo = ordinato[pos_min];
    for (int j = 0; j < ndata; j++)
    {
        pos_min = j;
        minimo = ordinato[pos_min];
        for (int i = j + 1; i < ndata; i++)
        {
            if (ordinato[i] < minimo)
            {
                minimo = ordinato[i];
                pos_min = i;
            }
        }
        double c = ordinato[j];
        ordinato[j] = ordinato[pos_min];
        ordinato[pos_min] = c;
    }
}

double mediana(int ndata, double *ordinato)
{
    int numero = 0;
    double mediana = 0;
    if (ndata % 2 == 0)
    {
        mediana = (ordinato[ndata / 2 - 1] + ordinato[ndata / 2]) / 2.;
    }
    else
    {
        mediana = ordinato[ndata / 2];
    }
    return mediana;
}

void Print(const double *data, int ndata) // a video
{
    for (int i = 0; i < ndata; i++)
    {
        cout << setw(5) << " giorno " << i + 1 << setw(5) << "" << data[i] << endl;
    }
}

void Print(const double *data, int ndata, const char *filename) // su file
{
    ofstream out(filename);
    for (int i = 0; i < ndata; i++)
    {
        out << setw(5) << " giorno " << i + 1 << setw(5) << "" << data[i] << endl;
    }
    out.close();
}
