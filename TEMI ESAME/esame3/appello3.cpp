// dati esame

#include "FunzioneVettoriale.h"
#include "gplot++.h"
#include "fmtlib.h"
#include "fstream"

using namespace std;
using namespace fmt;

int main(int argc, char *argv[])
{
    const double h = stod(argv[1]);

    if (argc != 2)
    {
        cerr << "Errore: inserire <eseguibile> e <grandezza passo>" << endl;
        exit(33);
    }

    TEMA eqdiff(0.0);
    RungeK<double, 4> rg;
    const double periodo = 2 * M_PI;

    // PUNTO 1
    fmt::println("#1 PUNTO");

    Gnuplot plt{};
    plt.redirect_to_png("output/Traiettoria.png", "1300, 1300");
    plt.multiplot(2, 2);
    array<double, 4> coor{1.0, 0.0, 0.0, 1.0};
    vector<double> x{}, y{};
    int conta{};
    for (double t = h; t <= 10.0 * periodo + h; t += h, conta++)
    {
        coor = rg.Passo(0, coor, h, eqdiff);
        // fmt::println("X = {:.3f}; Y = {:.3f}, conta = {}", coor[0], coor[1], conta);
        x.push_back(coor[0]);
        y.push_back(coor[1]);
    }
    cout << conta;
    plt.plot(x, y, "", Gnuplot::LineStyle::DOTS);
    plt.set_title("Traiettoria");
    plt.set_xlabel("X [metri]");
    plt.set_ylabel("Y [metri]");
    plt.show();
    fmt::println("X iniziale {}; X finale {:4f}", 1.0, coor[0]);
    fmt::println("Y iniziale {}; Y finale {:4f}", 0.0, coor[1]);

    // interpolazione
    double m = (y[conta - 1] - y[conta - 2]) / (x[conta - 1] - x[conta - 2]);
    cout << " m = " << m << endl;
    double q = y[conta - 1] - m * x[conta - 1];
    cout << " q = " << q << endl;

    double interpolazione = -q / m;
    fmt::println("Valore X interpolata = {:4f}", interpolazione);
    double differenza = abs(1.0 - interpolazione);
    fmt::println("La differenza della x in y = 0 = {:4f}", differenza);
    if (differenza < 1e-4)
    {
        fmt::print("#1 PUNTO verificato");
    }

    // PUNTO 2
    fmt::println("#2 PUNTO");
        conta=0;

    coor[0] = 1.1;
    coor[1] = 0.0;
    coor[2] = 0.0;
    coor[3] = 1.0;

    eqdiff.setAlfa(2.0);
    x.clear();
    y.clear();
    for (double t = h; t <= 10.0 * periodo + h; t += h, conta++)
    {
        coor = rg.Passo(0, coor, h, eqdiff);
        // fmt::println("X = {:.3f}; Y = {:.3f}, conta = {}", coor[0], coor[1], conta);
        x.push_back(coor[0]);
        y.push_back(coor[1]);
    }
    plt.plot(x, y, "", Gnuplot::LineStyle::DOTS);
    plt.set_title("Traiettoria alfa = 2");
    plt.set_xlabel("X [metri]");
    plt.set_ylabel("Y [metri]");
    plt.show();

        conta=0;


    coor[0] = 1.1;
    coor[1] = 0.0;
    coor[2] = 0.0;
    coor[3] = 1.0;

    eqdiff.setAlfa(-2.0);
    x.clear();
    y.clear();
    for (double t = h; t <= 10.0 * periodo + h; t += h, conta++)
    {
        coor = rg.Passo(0, coor, h, eqdiff);
        // fmt::println("X = {:.3f}; Y = {:.3f}, conta = {}", coor[0], coor[1], conta);
        x.push_back(coor[0]);
        y.push_back(coor[1]);
    }
    plt.plot(x, y, "", Gnuplot::LineStyle::DOTS);
    plt.set_title("Traiettoria alfa = -2");
    plt.set_xlabel("X [metri]");
    plt.set_ylabel("Y [metri]");
    plt.show();


    fmt::println("Per alfa = 2 diverge, per alfa = -2 oscilla attorno all'origine");
    fmt::println("#3 PUNTO");

    Gnuplot raggio{};
    raggio.redirect_to_png("output/Raggio.png");
    raggio.set_title("Andamento del raggio al variare del tempo");

    TEMA2 exam(2.0);
    conta=0;

    coor[0] = 1.1;
    coor[1] = 0.0;
    coor[2] = 0.0;
    coor[3] = 1.0;


    eqdiff.setAlfa(-2.0);
    x.clear();
    y.clear();
    vector <double> r{};
    vector <double> list_of_tempi{};
    for (double t = h; t <= 5.0 * periodo + h; t += h, conta++)
    {
        coor = rg.Passo(0, coor, h, exam);
        r.push_back(exam.raggio(coor));
        // fmt::println("X = {:.3f}; Y = {:.3f}, conta = {}", coor[0], coor[1], conta);
        x.push_back(coor[0]);
        y.push_back(coor[1]);
        list_of_tempi.push_back(t);
    }
    plt.plot(x, y, "", Gnuplot::LineStyle::DOTS);
    plt.set_title("Traiettoria alfa = -2 con eq differenziale 2");
    plt.set_xlabel("X [metri]");
    plt.set_ylabel("Y [metri]");
    plt.show();

    raggio.plot(list_of_tempi, r, "", Gnuplot::LineStyle::POINTS);
    raggio.show();


    return 0;
}