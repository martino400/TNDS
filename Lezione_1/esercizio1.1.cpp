#include <fstream>
#include <iostream>
#include <string>
// argc si becca il numero di parametri passati dalla linea di comando
// argv si becca i parametri passati dalla linea di comando
// il primo parametro è sempre il nome dell'eseguibile

//DA CONSEGNARE
using namespace std;

// per compilare --> g++ esercizio1.0.cpp  -Wall -o main

// dichiaro le funzioni

double media(int ndata, double *data);
double mediana(int ndata, double *data);
double varianza(int ndata, double *data, double media);
void ordina(int ndata, double *data, double *ordinato);

int main(int argc, char *argv[])
{

    const double g = 9.8;
    if (argc < 3)
    {
        cerr << "Uso del programma: " << argv[0] << " <n_data> <filename>\n";
        return 1;

        // questo serve per segnalare l'errore che passo meno di 3 parametri
    }

    int ndata = stoi(argv[1]); // stoi mi fa diventare argv[1] un intero che inserisco nella variabile ndata
    double *data = new double[ndata];

    const char *filename = argv[2];

    // leggo i dati dal file e li carico

    ifstream in(filename);

    if ( !in ) { 
      cout << "Non si riesce ad aprire file " << filename << endl;    
      exit(33);
    } else {
      for ( int k = 0 ; k < ndata ; k++ ) {
        if ( in.eof() ) { 
          cout << "Raggiunta fine file" << endl; 
          exit(33) ;      
        } 
        in >> data[k] ;
   
      }        
    }

    // calcolo media
    double average;
    average = media(ndata, data);
    cout << "La media = " << average << endl;

    // calcolo varianza
    double varianza1;
    varianza1 = varianza(ndata, data, average);

    cout << "La varianza è = " << varianza1 << endl;

    // selection sort
    double *ordinato = new double[ndata];
    ordina(ndata, data, ordinato);

    // calcolo mediana
    int numero = 0;
    double mediana1 = 0;
    mediana1 = mediana(ndata, ordinato);
    cout << "La mediana è = " << mediana1 << endl;

    // output su file

    ofstream out("output.txt");
    for (int i = 0; i < ndata; i++)
    {
        out << ordinato[i] << endl;
    }
    out.close();
    in.close();

    delete[] ordinato;
    delete[] data;
}

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
    double varianza1;
    for (int i = 0; i < ndata; i++)
    {
        varianza1 += pow(data[i] - media, 2);
        varianza1 /= ndata;
    }
    return varianza1;
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
        numero = ndata / 2;
        mediana = (ordinato[ndata / 2 - 1] + ordinato[ndata / 2]) / 2;
    }
    else
    {
        mediana = (ordinato[ndata / 2]);
    }
    return mediana;
}


// faccio bene la mediana