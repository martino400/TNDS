// dati esame

#include "FunzioneVettoriale.h"
#include "gplot++.h"
#include "fmtlib.h"
#include "fstream"
#include "IntegralMC.h"
#include "funzionebase.h"
#include "solutore.h"
#include "integral.h"
#include "Esperimento.h"

using namespace std;
using namespace fmt;

// E' LA MEDIA
double media(vector<double> data)
{
    double media{};

    for (int i = 0; i < ssize(data); i++)
    {
        media += data[i];
    }
    double val = double(media / ssize(data));
    return val;
}

// E' LA VARIANZA
double deviazione(vector<double> data, double media)
{
    double varianza = 0;
    for (int k = 0; k < data.size(); k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = double(varianza / (data.size() - 1.0));
    return (varianza);
}

double correlazione(vector<double> a, vector<double> b, vector<double> ab)
{
    return (media(ab) - media(a) * media(b)) / sqrt((deviazione(a, media(a)) * deviazione(b, media(b))));
}

int main(int argc, char *argv[])
{
    cout << endl
         << "PUNTO 1" << endl;
    const int n_iterazioni = 10000;
    
    double a{0};
    double &address = a;

    cout << &a << endl;
    cout << a << endl;
    cout << address << endl;
    // cout <<  << endl;



    return 0;
}