// dati esame

#include "FunzioneVettoriale.h"
#include "gplot++.h"
#include "fmtlib.h"
#include "fstream"
#include "IntegralMC.h"
#include "funzionebase.h"
#include "solutore.h"
#include "integral.h"

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

    bisezione metodo_bisezione;

    FunzioneEsame function;

    double x1 = metodo_bisezione.CercaZeriReference(1.0, 2.0, function, 1410065408, 0.01);
    fmt::println("Lo zero della funzione compreso tra [1,2] = {}", x1);
    double x2 = metodo_bisezione.CercaZeriReference(4.0, 5.0, function, 1410065408, 0.01);
    fmt::println("Lo zero della funzione compreso tra [4,5] = {}", x2);
    double x3 = metodo_bisezione.CercaZeriReference(7.0, 8.0, function, 1410065408, 0.01);
    fmt::println("Lo zero della funzione compreso tra [7,8] = {}", x3);

    cout << endl
         << "PUNTO 2" << endl;
    trapezio trap;
    double integrale = trap.integrate(x1, x2, 10, function);
    fmt::println("Lo zero della funzione compreso tra [{:.3f},{:.3f}] = {:4f}", x1, x2, integrale);

    cout << endl
         << "PUNTO 3" << endl;
    double integrale2 = trap.integrate(x1, x2, 20, function);

    double errore = abs(integrale2 - integrale) * 4.0 / 3.0;
    fmt::println("Errore rispetto al valore vero integrando tra [{:.3f},{:.3f}] con 10 punti = {:4f}", x1, x2, errore);

    double h = (x2 - x1) / 10.0;
    cout << endl
         << "PUNTO 4" << endl;

    double passo_h = sqrt(0.001 * 3.0 * h * h / (4.0 * abs(integrale2 - integrale)));
    double N_passi_necessari = round(abs(x2 - x1) / passo_h);

    fmt::println("N passi necessari per avere una precisione di 0.001 integrando tra [{:.3f},{:.3f}] con 10 punti = {}", x1, x2, N_passi_necessari);

    cout << endl
         << "PUNTO 5" << endl;

    IntegraMedia int_media(1);

    vector<double> valore_integrale{};

    for (int i = 0; i < 10000; i++)
    {
        valore_integrale.push_back(int_media.valore(function, x1, x2, NAN, 16)); // non mi serve sapere fmax in IntegraMedia
    }
    double devstd = sqrt(deviazione(valore_integrale, media(valore_integrale)));

    double Numero_necessario = round(devstd * devstd * 16 / (0.001 * 0.001));

    fmt::println("Quantità di punti necessari = {:4f}", Numero_necessario);

    cout << endl
         << "PUNTO 6" << endl;
    fmt::println("Plot salvato in FunioneIntegrale.png", Numero_necessario);

    valore_integrale.clear();
    vector<double> valore_t{};
    vector<double> valore_funzione{};

    Gnuplot F{};
    F.redirect_to_png("FunioneIntegrale.png", "1000, 1000");
    F.multiplot(2, 1);
    F.set_title("Funzione integrale");

    for (double t = x1; t <= x3; t += 0.1)
    {
        valore_integrale.push_back(trap.integrate(x1, t, 10, function));
        valore_t.push_back(t);
        valore_funzione.push_back(function.eval(t));
    }

    F.plot(valore_t, valore_integrale);
    F.set_xlabel("X");
    F.set_ylabel("Valore Funzione Integrale");
    F.show();
    F.set_title("Funzione");
    F.plot(valore_t, valore_funzione);
    F.set_xlabel("X");
    F.set_ylabel("Valore Funzione");
    F.show();

    return 0;
}