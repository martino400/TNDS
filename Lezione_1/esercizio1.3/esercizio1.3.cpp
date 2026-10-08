#include "funzioni.h"

int main(int argc, char *argv[])
{
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

    Print(data, ndata);               // stampa a video
    Print(data, ndata, "output.txt"); // stampa su file

    in.close();

    delete[] ordinato;
    delete[] data;
}

// faccio bene la mediana