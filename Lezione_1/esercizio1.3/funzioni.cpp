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

    varianza = varianza / (double(ndata)-1.0);
    return varianza;
}

void scambiaRef(double& a, double& b)
{
    double c;
    c = a;
    a = b;
    b = c;
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

void selection_sort(double * vec, int size) {
  for(int j = 0; j < size - 1; ++j) {
      int imin = j;
      double min = vec[imin];
      for(int i = j + 1; i < size; ++i) {
          if(vec[i] < min) {
            //trova qual'è il più piccolo da j a size, una volta trovato scambia il più piccolo con il j esimo 
            //poi si passa a j+1
              min = vec[i];
              imin = i;
          }
      }

      scambiaRef(vec[j], vec[imin]);
      // equivalente:
      // scambiaByPointer(vec + j, vec + imin);
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
