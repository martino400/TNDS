// dati esame

#include "FunzioneVettoriale.h"
#include "gplot++.h"
#include "fmtlib.h"
#include "fstream"
#include "Esperimento.h"
#include "RandomGen.h"

using namespace std;
using namespace fmt;

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

int main(int argc, char *argv[])
{
    cout << endl
         << "PUNTO 1" << endl;
    if (argc != 2)
    {
        cerr << "Inserire <eseguibile> e <grandezza passo integrazione = 0.02>" << endl;
    }
    const double h = stod(argv[1]);

    ArmonicoSmorzato smorzato(1.15, 0.01);

    RungeK<double, 2> rg;

    array<double, 2> coordinate{1.0, 0};

    vector<double> list_of_x{};
    vector<double> list_of_t{};

    Gnuplot plot{};
    plot.redirect_to_png("Output2/LeggeOraria.png", "1000,1000");
    plot.multiplot(2, 1);

    cout << endl
         << "PUNTO 1" << endl;
    double t = h;
    int conta = 0;
    while (t <= 43.0 + h)
    {
        coordinate = rg.Passo(t, coordinate, h, smorzato);
        fmt::println(" x = {} [m] , v_x = {:.3e} [m/s] , t = {:.3e} [sec], conta = {}", coordinate[0], coordinate[1], t, conta);
        list_of_x.push_back(coordinate[0]);
        list_of_t.push_back(t);
        t += h;
        conta++;
    }
    plot.set_xlabel("Tempi [secondi]");
    plot.set_ylabel("Metri [metri]");
    plot.set_title("Legge Oraria");
    plot.plot(list_of_t, list_of_x, "", Gnuplot::LineStyle::POINTS);
    plot.show();

    double m = (list_of_x[conta - 1] - list_of_x[conta - 2]) / (list_of_t[conta - 1] - list_of_t[conta - 2]);
    double q = list_of_x[conta - 1] - m * list_of_t[conta - 1];
    double x1 = m * 43.0 + q;

    // DA FARE INTERPOLAZIONE!

    // PUNTO 2
    const double h2 = h / 2.0;
    t = h2;
    coordinate[0] = 1.0;
    coordinate[1] = 0.0;
    conta = 0;

    list_of_t.clear();
    list_of_x.clear();

    while (t <= 43.0)
    {
        coordinate = rg.Passo(t, coordinate, h2, smorzato);
        fmt::println(" x = {} [m] , v_x = {:.3e} [m/s] , t = {:.3e} [sec], conta = {}", coordinate[0], coordinate[1], t, conta);
        list_of_t.push_back(t);
        list_of_x.push_back(coordinate[0]);
        t += h2;
        conta++;
    }
    cout << conta << endl;
    // faccio interpolazione!

    m = (list_of_x[conta - 1] - list_of_x[conta - 2]) / (list_of_t[conta - 1] - list_of_t[conta - 2]);
    q = list_of_x[conta - 1] - m * list_of_t[conta - 1];
    double x2 = m * 43.0 + q;
    double errore = abs(x1 - x2) * 16.0 / 15.0;
    cout << endl
         << "PUNTO 2" << endl;
    fmt::println("Errore = {}, i due punti sono x1 = {:4f} ; x2 = {:4f}", errore, x1, x2);

    //  PUNTO 3

    cout << endl
         << "PUNTO 3" << endl;
    double passo_h = pow(5e-5 * 15.0 / 16.0 * pow(0.1, 4) / abs(x1 - x2), 1.0 / 4.0);
    fmt::println("Passo per avere un errore 5e-5 = {}", passo_h);

    // PUNTO 4

    cout << endl
         << "PUNTO 4" << endl;
    RandomGen rand(1);

    list_of_t.clear();
    list_of_x.clear();
    for (int i = 0; i < 10000; i++)
    {
        coordinate[0] = 1.0;
        coordinate[1] = rand.GaussBOXMULLER(0.0, 3e-3);
        t = 0;
        while (t <= 43.0)
        {
            coordinate = rg.Passo(t, coordinate, h, smorzato);
            t += h;
        }
        list_of_x.push_back(coordinate[0]);
    }
    plot.histogram(list_of_x, 70, "Histogram distribution after Runge Kutta");
    plot.set_ylabel("");
    plot.set_xlabel("Distanza [metri]");
    plot.show();

    fmt::println("Plot salvato in Output2/LeggeOraria.png");

    cout << endl
         << "PUNTO 5" << endl;
    Gnuplot Distirbuzioni{};
    Distirbuzioni.redirect_to_png("Output2/Distribuzioni.png", "1000, 1000");
    Distirbuzioni.multiplot(3, 2);
    const vector<double> sigma{3e-3, 5e-3, 8e-3, 12e-3, 15e-3};
    vector<double> list_of_average{};
    vector<double> list_of_stddev{};

    for (int k = 0; k < 5; k++)
    {
        list_of_x.clear();
        for (int i = 0; i < 10000; i++)
        {
            coordinate[0] = 1.0;
            coordinate[1] = rand.GaussBOXMULLER(0.0, sigma[k]);
            t = 0;
            while (t <= 43.0)
            {
                coordinate = rg.Passo(t, coordinate, h, smorzato);
                t += h;
            }
            list_of_x.push_back(coordinate[0]);
        }
        list_of_average.push_back(media(list_of_x));
        list_of_stddev.push_back(sqrt(deviazione(list_of_x, media(list_of_x))));
        Distirbuzioni.histogram(list_of_x, 70, "Histogram distribution after Runge Kutta");
        Distirbuzioni.set_ylabel("");
        Distirbuzioni.set_xrange(0.53, 0.58);
        Distirbuzioni.set_xlabel("Spazio [metri]");
        Distirbuzioni.show();
    }

    for(int i=0; i<5; i++)
    {
        fmt::println("Media = {:4f}  per errore iniziale = {:4f}   e deviazione ottenuta = {:4f}", list_of_average[i], sigma[i], list_of_stddev[i]);
    }

    Distirbuzioni.plot(sigma, list_of_stddev, "",  Gnuplot::LineStyle::POINTS);
    Distirbuzioni.set_title("Grafico delle deviazioni al variare della v_0");
    Distirbuzioni.show();

    fmt::println("Plot salvato in Distribuzioni.png");

    return 0;
}