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
    const double carica = 1.60e-19;     // Coulomb
    const double campo_magnetico = 0.5; // Tesla
    const double vel_iniziale = 91500;

    const double h_integrazione = 1.E-8;

    const double mNe20 = 20 * 1.66 * pow(10, -27);

    Forza_Lorentz campo(mNe20, carica, campo_magnetico);

    Forza_LorentzNonOmogenea campo1(mNe20, carica, campo_magnetico);

    array<double, 4> coordinate{0.0, 0.0, vel_iniziale, 0.0};

    RungeK<double, 4> Rg;
    double d{};
    vector<double> x{};
    vector<double> y{};
    Gnuplot plot{};
    plot.redirect_to_png("Plot.png", "1500, 1500");
    plot.multiplot(2, 2);
    do
    {
        d = coordinate[0]; // controllo che sia maggiore di 0;
        x.push_back(coordinate[0]);
        y.push_back(coordinate[1]);
        // cout << "x: " << coordinate[0] << ", y: " << coordinate[1] << ", vx: " << coordinate[2] << ", vy: " << coordinate[3] << endl;
        coordinate = Rg.Passo(0.0, coordinate, h_integrazione, campo);

    } while (coordinate[0] * d >= 0);
    x.push_back(coordinate[0]);
    y.push_back(coordinate[1]);
    d = coordinate[1];
    plot.plot(x, y);
    plot.set_title("Traiettoria Ne20");
    plot.show();
    fmt::println("La coordinata y nel momento in cui assume x < 0 = {}", d);

    x.clear();
    y.clear();
    coordinate[0] = 0.0;
    coordinate[1] = 0.0;
    coordinate[2] = vel_iniziale;
    coordinate[3] = 0.0;

    cout << endl
         << "PUNTO 2" << endl;
    do
    {
        d = coordinate[0]; // controllo che sia maggiore di 0;
        x.push_back(coordinate[0]);
        y.push_back(coordinate[1]);
        coordinate = Rg.Passo(0.0, coordinate, h_integrazione, campo1);

    } while (coordinate[0] * d >= 0);
    x.push_back(coordinate[0]);
    y.push_back(coordinate[1]);
    d = coordinate[1];
    plot.plot(x, y);
    plot.set_title("Traiettoria Ne22");
    plot.show();
    // devo interpolare ma interpolando di sicuro non cambia chissà quanto
    fmt::println("La coordinata y nel momento in cui assume x < 0 = {}", d);

    cout << endl
         << "PUNTO 3" << endl;
    const double mNe22 = 22 * 1.66 * pow(10, -27);
    coordinate[0] = 0.0;
    coordinate[1] = 0.0;
    coordinate[2] = vel_iniziale;
    coordinate[3] = 0.0;

    double d2{};

    campo1.setMassa(mNe22);

    do
    {
        d2 = coordinate[0];
        coordinate = Rg.Passo(0.0, coordinate, h_integrazione, campo1);
    } while (coordinate[0] * d2 >= 0);
    d2 = coordinate[1];
    fmt::println("D con ioni Ne22 = {}", d2);
    fmt::println("Differenza tra d con Ne20 e d con Ne22 = {}", abs(d2 - d));

    cout << endl
         << "PUNTO 4" << endl;
    campo1.setMassa(mNe22);
    RandomGen rand(3);

    vector<double> distanzaNa20{};
    vector<double> distanzaNa22{};

    for (int i = 0; i < 10000; i++)
    {
        coordinate[0] = 0.0;
        coordinate[1] = 0.0;
        coordinate[2] = rand.GaussBOXMULLER(vel_iniziale, 0.01 * vel_iniziale);
        coordinate[3] = 0.0;
        d2 = 0;
        do
        {
            d2 = coordinate[0]; // controllo che sia maggiore di 0;
            coordinate = Rg.Passo(0.0, coordinate, h_integrazione, campo1);
        } while (coordinate[0] * d2 >= 0);
        d2 = coordinate[1];
        distanzaNa22.push_back(d2);
    }

    campo1.setMassa(mNe20);
    for (int i = 0; i < 10000; i++)
    {
        coordinate[0] = 0.0;
        coordinate[1] = 0.0;
        coordinate[2] = rand.GaussBOXMULLER(vel_iniziale, 0.01 * vel_iniziale);
        coordinate[3] = 0.0;
        d2 = 0;
        do
        {
            d2 = coordinate[0]; // controllo che sia maggiore di 0;
            coordinate = Rg.Passo(0.0, coordinate, h_integrazione, campo1);
        } while (coordinate[0] * d2 >= 0);
        d2 = coordinate[1];
        distanzaNa20.push_back(d2);
    }
    plot.histogram(distanzaNa20, 100, "Histogramma con ioni Ne20");
    plot.set_title("Istogramma posizione finale ioni Ne20");
    plot.show();
    plot.histogram(distanzaNa22, 100, "Histogramma con ioni Ne22");
    plot.set_title("Istogramma posizione finale ioni Ne22");
    plot.show();

    fmt::println("La deviazione della distanza misurata per ioni Ne20 = {}", sqrt(deviazione(distanzaNa20, media(distanzaNa20))));
    fmt::println("La deviazione della distanza misurata per ioni Ne22 = {}", sqrt(deviazione(distanzaNa22, media(distanzaNa22))));

    double devNa20 = sqrt(deviazione(distanzaNa20, media(distanzaNa20)));
    double devNa22 = sqrt(deviazione(distanzaNa22, media(distanzaNa22)));
    double Na20{};
    double Na22{};

    cout << endl
         << "PUNTO 5" << endl;

    // fisso le medie

    Na20 = media(distanzaNa20);
    Na22 = media(distanzaNa22);
    fmt::println("Media Na20 ={} ", Na20);
    fmt::println("Media Na22 = {}", Na22);

    fmt::println("ABS = {}", abs(Na20 - Na22));

    fmt::println("3 devNa22 = {}", 3 * devNa22);

    // prendo na22 perchè è quella con la deviazione standard più piccola,
    // per vedere se sono risolte per quella più piccola alloora saranno risolte anche per quella più grande

    if (abs(Na20 - Na22) > 3 * devNa22 || abs(Na20 - Na22) > 3 * devNa20)
    {
        fmt::println("Le due linee sono risolte o per la deviazione standard degli ioni Na22 o per quella degli ioni Na20");
    }
    else
    {
        fmt::println("Le due linee non risolte nè per la deviazione standard degli ioni Na22 nè per quella degli ioni Na20");
    }

    // cancolo dell'errore per il passo

    cout << endl
         << "PUNTO 6" << endl;
    double dmezzi{};

    coordinate[0] = 0.0;
    coordinate[1] = 0.0;
    coordinate[2] = vel_iniziale;
    coordinate[3] = 0.0;
    do
    {
        dmezzi = coordinate[0]; // controllo che sia maggiore di 0;
        coordinate = Rg.Passo(0.0, coordinate, h_integrazione / 2.0, campo1);

    } while (coordinate[0] * dmezzi >= 0);
    dmezzi = coordinate[1];

    double errore_integrazione = 16.0 / 15.0 * abs(dmezzi - d);

    if (10 * errore_integrazione < abs(Na20 - Na22))
    {
        fmt::println("l'errore numerico sulla stima di d è almeno 10 volte inferiore alla distanza tra i valori medi dei picchi");
    }

    return 0;
}