// dati esame

#include "FunzioneVettoriale.h"
#include "gplot++.h"
#include "fmtlib.h"
#include "fstream"
#include "Esperimento.h"
#include "RandomGen.h"
#include "funzionebase.h"
#include "solutore.h"
#include <cassert>

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


//test del TOMASI
bool are_close(double a, double b, double eps = 1.0e-4) {
  return abs(a - b) < eps;
}

void test_code()
{
    const double target_prec{1e-4};
    double d = 100e-6;
    double L = 1;
    double lambda = 500e-9;
    func function(d, 500e-9, L);
    assert(are_close(function.eval(0.05), -0.192375, target_prec));
    cerr << "Hurrah! All tests have passed!\n";
}

int main(int argc, char *argv[])
{
    test_code();
    cout << endl
         << "PUNTO 1" << endl;
    if (argc != 2)
    {
        cerr << "Inserire <eseguibile> e <grandezza passo integrazione = 0.02>" << endl;
    }
    const double h = stod(argv[1]);

    vector<double> integrale, argomento;
    double d = 100e-6;
    double L = 1;
    double lambda = 500e-9;

    // PUNTO1
    Gnuplot plot;
    func function(d, lambda, L);
    plot.redirect_to_png("Output/Integrale.png", "1000, 1000");
    for (double x = -0.1; x <= 0.1; x += 0.0001)
    {
        integrale.push_back(function.eval(x));
        argomento.push_back(x);
    }
    plot.set_title("Diffrazione attraverso fenditura d");
    fmt::println("Plot salvato in Output/Integrale.png");
    plot.set_ylabel("A(x)");
    plot.set_xlabel("x");
    plot.plot(argomento, integrale);
    plot.show();

    cout << endl
         << "PUNTO 2" << endl;
    // PUNTO 2
    // la funzione è simmetrica rispetto all'asse y
    double x = 0, min;

    vector<double> lunghezze_onda{500e-9, 400e-9, 450e-9};

    for (int k = 0; k < 3; k++)
    {
        fmt::println("Lunghezza d'onda = {} [metri]", lunghezze_onda[k]);
        func function(d, lunghezze_onda[k], L);
        x = 0, min = 0;
        bisezione metodo;
        for (int i = 0; i <= 2; i++)
        {
            x = metodo.CercaZeriReference(0.04 * i, (i + 1.0) * 0.04, function, 1e9, 0.000001);
            if (i == 0)
            {
                min = x;
            }
            fmt::println("X_0 ({}) = {} [metri]", i + 1, x);
            if (fabs(x) < min)
            {
                min = fabs(x);
            }
        }
        fmt::println("x_0 minimo della funzione tale che A(x_0) = 0 è pari a {} [metri] e precisione pari a {}  [metri]", min, 1e-6);
        cout << endl;
    }

    return 0;
}