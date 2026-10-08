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
#include "VectorOperations.h"

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
    const double passo_h = 0.1;
    const double passo_h2 = 0.01;
    const double massa_razzo = 500;
    const double angolo_iniziale = M_PI / 3.0;
    const double spint = 80000;
    const double g = 9.80665;

    SpintaIniziale eqdiff(angolo_iniziale, spint, massa_razzo);
    RungeK<double, 4> rg;

    array<double, 4> iniziali{0.0, 0.0, 0.0, 0.0};
    array<double, 4> CI = iniziali;

    Gnuplot plot{};
    plot.redirect_to_png("Plot.png", "1000,1000");
    plot.multiplot(1, 1);
    vector<double> coordianta_x{};
    vector<double> coordianta_y{};
    double t = 0;
    while (iniziali[1] >= 0.0)
    {
        coordianta_x.push_back(iniziali[0]);
        coordianta_y.push_back(iniziali[1]);
        iniziali = rg.Passo(t, iniziali, passo_h, eqdiff);
        fmt::println("Coordinata X = {:4f} ; Y = {:4f}", iniziali[0], iniziali[1]);
        t += passo_h;
    }
    plot.plot(coordianta_x, coordianta_y, "Plot h = 0.1 s");
    t = 0;
    coordianta_x.clear();
    coordianta_y.clear();
    iniziali = CI;
    while (iniziali[1] >= 0.0)
    {
        coordianta_x.push_back(iniziali[0]);
        coordianta_y.push_back(iniziali[1]);
        iniziali = rg.Passo(t, iniziali, passo_h2, eqdiff);
        fmt::println("Coordinata X = {:4f} ; Y = {:4f}", iniziali[0], iniziali[1]);
        t += passo_h2;
    }
    plot.plot(coordianta_x, coordianta_y, "Plot h = 0.01 s");
    plot.show();

    cout << endl
         << "PUNTO 2" << endl;

    // risolvo le equazioni del moto

    array<double, 4> Val_veri{
        1.0 / 2.0 * spint / massa_razzo * cos(angolo_iniziale),
        1.0 / 2.0 * (-g + spint / massa_razzo * sin(angolo_iniziale)),
        spint / massa_razzo * cos(angolo_iniziale),
        (-g + spint / massa_razzo * sin(angolo_iniziale))};

    double passo_integrazione = 1;
    double err1{1}, err2{1}, err3{1}, err4{1};
    double h;

    while ((err1 > 10e-4) || (err2 > 10e-4) || (err3 > 10e-4) || (err4 > 10e-4))
    {
        // cout << err1 << endl;
        iniziali = CI;
        t = 0.0;
        double nsteps = round(1.0 / passo_integrazione);
        h = 1.0 / nsteps;
        for (int i = 0; i < nsteps; i++)
        {
            iniziali = rg.Passo(t, iniziali, h, eqdiff);
            t += h;
        }
        passo_integrazione -= 0.000001;

        err1 = fabs(iniziali[0] - Val_veri[0]) / iniziali[0];
        err2 = fabs(iniziali[1] - Val_veri[1]) / iniziali[1];
        err3 = fabs(iniziali[2] - Val_veri[2]) / iniziali[2];
        err4 = fabs(iniziali[3] - Val_veri[3]) / iniziali[3];

        cout << h << endl;
    }

    fmt::println("Passo necessario per trovare un errore minore che di 10^-4 in 1 sec = {:4f}", h);
    fmt::println("x = {:4f}; Y = {:4f}; vx = {:4f}; vy = {:4f}", iniziali[0], iniziali[1], iniziali[2], iniziali[3]);
    fmt::println("x = {:4f}; Y = {:4f}; vx = {:4f}; vy = {:4f}", Val_veri[0], Val_veri[1], Val_veri[2], Val_veri[3]);

    cout << endl
         << "PUNTO 3" << endl;

    iniziali = CI;
    t = 0.0;

    coordianta_x.clear();
    coordianta_y.clear();
    int conta = 0;
    while (iniziali[1] >= 0.0)
    {
        iniziali = rg.Passo(t, iniziali, h, eqdiff);
        conta++;
        coordianta_x.push_back(iniziali[0]);
        coordianta_y.push_back(iniziali[1]);
        // fmt::println("Coordinata X = {:4f} ; Y = {:4f} ; conta = {}", iniziali[0], iniziali[1], conta);
        t += h;
    }
    fmt::println("COORDINATE GITTATA = Coordinata X = {:4f} ; Y = {:4f} ; conta = {}", iniziali[0], iniziali[1], conta);
    // double m = (coordianta_y.at(conta) - coordianta_y.at(conta-1))/coordina
    return 0;
}