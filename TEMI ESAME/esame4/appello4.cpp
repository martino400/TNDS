// dati esame

#include "FunzioneVettoriale.h"
#include "gplot++.h"
#include "fmtlib.h"
#include "fstream"
#include "Esperimento.h"
#include "IntegralMC.h"
#include "funzionebase.h"
#include "integral.h"
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

bool are_close(double a, double b, double eps = 1.0e-7)
{
    return abs(a - b) < eps;
}

void test_code()
{
    // I test per `Funzione1` restano invariati
    // ...

    f_x2 fun2;
    assert(are_close(fun2.eval(0.0), 0.5));
    assert(are_close(fun2.eval(1.0), 1.0 / sqrt(3.0)));
    assert(isinf(fun2.eval(2.0)));

    f_x fun1;
    const double e = 2.71828182845904523536;

    // I valori attesi sono calcolabili a mano
    assert(are_close(fun1.eval(0.0), 0.0));
    assert(are_close(fun1.eval(1.0), 0.5 * log(e + 1)));
    assert(are_close(fun1.eval(2.0), 8.0 * log(sqrt(e + 4.0))));

    sinx seno{};
    midright midright{};
  assert(are_close(midright.integrate(0.0, 1.0, 1, seno),
                   sin(1.0)));
  assert(are_close(midright.integrate(0.0, 1.0, 2, seno),
                   (sin(0.5) + sin(1.0)) / 2));
    cout << "Passato gli assert, good to go!" << endl;
}

int main(int argc, char *argv[])
{
    test_code();
    const double e = 2.71828182845904523536;
    const double pi_2 = M_PI_2;
    cout << endl
         << "PUNTO 1" << endl;

    Gnuplot andamento_errore{};
    andamento_errore.redirect_to_png("Output/AndamentoErroreMidpoint.png", "1000, 1000");

    midpoint mid;
    f_x funzione;

    vector<double> errori_finali{};
    vector<int> numero_pt;

    const double valore_vero = 3.0 / 16.0 * e * e;
    cout << "========================================" << endl
         << "MIDPOINT" << endl
         << "========================================" << endl;
    for (int n_punti = 2; n_punti <= 1024; n_punti = n_punti * 2)
    {
        errori_finali.push_back(abs(valore_vero - mid.integrate(0.0, sqrt(e), n_punti, funzione)));
        numero_pt.push_back(n_punti);

        fmt::println("{}      {:4f}      {:4f}", n_punti, abs(valore_vero - mid.integrate(0.0, sqrt(e), n_punti, funzione)), mid.integrate(0.0, sqrt(e), n_punti, funzione));
    }
    andamento_errore.plot(numero_pt, errori_finali);
    andamento_errore.set_xlabel("Numero Punti Usati per l'integrazione");
    andamento_errore.set_ylabel("Delta rispetto al valore vero");
    andamento_errore.set_title("Andamento Errore");
    andamento_errore.set_logscale(Gnuplot::AxisScale::LOGXY);
    andamento_errore.show();

    cout << endl
         << "PUNTO 2" << endl;
    vector<double> h;
    for (double i = 2; i <= 1024; i = i * 2)
    {
        h.push_back(log(sqrt(e) / i));
    }

    vector<double> err{};
    for (int n_punti = 2; n_punti <= 1024; n_punti = n_punti * 2)
    {
        err.push_back(log(abs(valore_vero - mid.integrate(0.0, sqrt(e), n_punti, funzione))));
    }

    double k2 = (err[6] - err[0]) / (h[6] - h[0]);
    double k1 = pow(e, err[0] - k2 * h[0]);
    fmt::println("Errore integrazione = {:4f}h^{:4f}", k1, k2);

    // VENGONO CON ENTRAMBI I METODI --> TOP

    andamento_errore.redirect_to_png("Output/AndamentoErroreMidright.png", "1000, 1000");
    cout << endl
         << "PUNTO 3" << endl;
    errori_finali.clear();
    numero_pt.clear();
    midright mid_destra;
    cout << "========================================" << endl
         << "MidRIGHT" << endl
         << "========================================" << endl;
    for (int n_punti = 2; n_punti <= 1024; n_punti = n_punti * 2)
    {
        errori_finali.push_back(abs(valore_vero - mid_destra.integrate(0.0, sqrt(e), n_punti, funzione)));
        numero_pt.push_back(n_punti);
        fmt::println("{}      {}      {:4f}", n_punti, abs(valore_vero - mid_destra.integrate(0.0, sqrt(e), n_punti, funzione)), mid_destra.integrate(0.0, sqrt(e), n_punti, funzione));
    }
    andamento_errore.plot(numero_pt, errori_finali);
    andamento_errore.set_xlabel("Numero Punti Usati per l'integrazione");
    andamento_errore.set_ylabel("Delta rispetto al valore vero");
    andamento_errore.set_title("Andamento Errore Midright");
    andamento_errore.set_logscale(Gnuplot::AxisScale::LOGXY);
    andamento_errore.show();

    cout << endl
         << "PUNTO 4: corretto" << endl;
    err.clear();
    for (int n_punti = 2; n_punti <= 1024; n_punti = n_punti * 2)
    {
        err.push_back(log(abs(valore_vero - mid_destra.integrate(0.0, sqrt(e), n_punti, funzione))));
    }
    // sto lavorando con err che sono dei log( ... )
    k2 = (err[6] - err[0]) / (h[6] - h[0]);
    k1 = pow(e, err[0]) / pow(pow(e, h[0]), k2);

    fmt::println("Andamento errore midright = {:4f} h ^ {:4f}", k1, k2);

    cout << endl
         << "PUNTO 5" << endl;
    vector<double> int_media{};
    IntegraMedia integral(3);
    for (int i = 0; i < 1000; i++)
    {
        int_media.push_back(integral.valore(funzione, 0, sqrt(e), 0, 16));
    }
    double average = media(int_media);
    double dev = sqrt(deviazione(int_media, average));

    // NON BISOGNA METTERE LA MEDIA MA UN VALORE QUALSIASI DI QUESTI
    fmt::println("Valore integrale con metodo della MEDIA = {}, con DEV_STD = {}", int_media.at(7), dev);

    cout << endl
         << "PUNTO 6" << endl;
    double precisione_desiderata = abs(valore_vero - mid.integrate(0.0, sqrt(e), 16, funzione));
    double numero_desiderata = (dev * dev) * 16.0 / (precisione_desiderata * precisione_desiderata);
    fmt::println("Quantità di punti circa necessari per ottenere una precisione = {}  --> {:4f}", round(numero_desiderata), precisione_desiderata);

    cout << endl
         << "PUNTO 7" << endl;

    f_x2 funzione2;
    cout << "========================================" << endl
         << "MidRIGHT" << endl
         << "========================================" << endl;
    for (int n_punti = 2; n_punti <= 1024; n_punti = n_punti * 2)
    {
        fmt::println("{}           {:4f}", n_punti, mid_destra.integrate(0.0, 2, n_punti, funzione2));
    }
    cout << "========================================" << endl
         << "MidPOINT" << endl
         << "========================================" << endl;
    for (int n_punti = 2; n_punti <= 1024; n_punti = n_punti * 2)
    {
        fmt::println("{}           {:4f}", n_punti, mid.integrate(0.0, 2, n_punti, funzione2));
    }
    err.clear();
    for (int n_punti = 2; n_punti <= 1024; n_punti = n_punti * 2)
    {
        err.push_back(log(abs(pi_2 - mid.integrate(0.0, 2, n_punti, funzione2))));
    }
    h.clear();

    for (double i = 2; i <= 1024; i = i * 2)
    {
        h.push_back(log(sqrt(2.0) / i));
    }
    k2 = (err[6] - err[0]) / (h[6] - h[0]);
    k1 = pow(e, err[0]) / pow(pow(e, h[0]), k2);

    fmt::println("Non riesce a calcolare il valore il metodo midRIGHT perchè cerca di calcolare il \n valore della funzione in x = 2 ma questo viene = infinito \n per questo ritorna errore in tutti gli integrali. \nQuello Midpoint invece di ferma poco prima e non arriva fino a toccare proprio x = 2");

    fmt::println("Valore di k2 in questo caso = {:4f}", k2);
    fmt::println("Valore di K1 in questo caso = {}", k1);
    return 0;
}