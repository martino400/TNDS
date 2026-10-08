#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <cassert>
#include "VectorOperations.h"
#include "fmtlib.h"
#include "FunzioneVettoriale.h"
#include "gplot++.h"
#include <fstream>

using namespace std;

void test_operations()
{
    array x{1.0, 2.0, 3.0};
    array y{2.0, 1.0, 0.0};
    array<double, 3> z, z1;
    z = x + y;
    if (z[0] == 3.0 && z[1] == 3.0 && z[2] == 3.0)
    {
        fmt::println("Il + Funziona tutto bene alla grande! IUPPI!");
    }
    z1 = x - y;
    if (z1[0] == -1.0 && z1[1] == 1.0 && z1[2] == 3.0)
    {
        fmt::println("Il - Funziona tutto bene alla grande! IUPPI!");
    }
}

inline double are_close(double a, double b, double eps = 1e-7)
{
    return abs(a - b) < eps;
}

inline void test_euler()
{
    Eulero<double, 2> my_euler{};

    OscillatoreArmonico osc(1.0);

    const double tmax{0.91}; // È più sicuro usare qualcosa di più di 0.9
    const double h{0.1};
    array<double, 2> x{0.0, 1.}; // x0 =0  v0 =1.0
    double t{};

    const int num_of_steps{(int)lround(tmax / h)};

    // evoluzione del sistema fino a 0.9 s
    for (int step{}; step < num_of_steps; step++)
    {
        x = my_euler.Passo(t, x, h, osc);
        t = t + h;
    }

    assert(are_close(x[0], 0.817256, 1e-6));
    assert(are_close(x[1], 0.652516, 1e-6));
    fmt::println("funziona test_eulero!!!!!!");
}

inline void test_rg()
{
    RungeK<double, 2> my_euler{};

    OscillatoreArmonico osc(1.0);

    const double tmax{0.11}; // È più sicuro usare qualcosa di più di 0.9
    const double h{0.1};
    array<double, 2> x{0.0, 1.}; // x0 =0  v0 =1.0
    double t{};

    const int num_of_steps{(int)lround(tmax / h)};

    // evoluzione del sistema fino a 0.9 s
    for (int step{}; step < num_of_steps; step++)
    {
        x = my_euler.Passo(t, x, h, osc);
        t = t + h;
    }

    assert(are_close(x[0], 0.0998333, 1e-6));
    assert(are_close(x[1], 0.995004, 1e-6));
    fmt::println("funziona test_runge kutta!!!!!!");
}

// t va da 0 a 70 secondi
// h compreso tra 0.1 e 0.001 secondi --> meno di 0.001 secondi e ci mette troppo il programma
int main(int argc, char *argv[])
{
    test_operations();
    test_euler();
    test_rg();
    if (argc != 2)
    {
        fmt::println("Problema su come è stato eseguito il programma! Devi inserire <eseguibile> e <grandezza passo>");
        exit(-1);
    }

    // for starters...

    RungeK<double, 2> rgk;
    Pendolo pendulum(1.0, 9.789);

    // tempi...

    const double tmax{10.0};
    const double h{stof(argv[1])};
    double t{};
    int num_of_steps{(int)lround(tmax / h)};
    std::vector<double> list_of_t;
    std::vector<double> list_of_x;

    // PLOT PENDOLO
    array<double, 2> x{-1.0, 0.0};
    Gnuplot plt1{};

    for (int i = 0; i < num_of_steps; i++)
    {
        // Salva le coordinate del punto (t, x)
        list_of_t.push_back(t);
        list_of_x.push_back(x[1]);

        // Stampa i risultati in forma di tabella

        // “Avanza” di un passo `h` la soluzione in `x`
        x = rgk.Passo(t, x, h, pendulum);
        t = t + h;
    }

    std::string filename1{"PLOTPendolo.png"};
    plt1.redirect_to_png(filename1);
    plt1.plot(list_of_t, list_of_x, "", Gnuplot::LineStyle::LINESPOINTS);

    plt1.set_xlabel("Ampiezza [m]");
    plt1.set_ylabel("Tempo [s]");
    plt1.show();

    // GRAFICO PERIODO IN FUNZIONE DELL'AMPIEZZA DI OSCILLAZIONE DI PARTENZA
    Gnuplot plt{};
    std::vector<double> list_of_Periodi;
    std::vector<double> list_of_Ampiezze;
    double m{}, q{};
    for (double i = 0.1; i <= 3; i += 0.01)
    {
        array<double, 2> x{i, 0.0};
        double told{}, vold{};
        t = 0;
        while (x[1] <= 0)
        {
            vold = x[1];
            told = t;
            x = rgk.Passo(t, x, h, pendulum);
            t = t + h;
        }
        // metodo di INTERPOLAZIONE, ossia creo una retta v_old e v e t old e t
        m = (vold - x[1]) / (told - t); // giusto che m vengano tutte negative
        q = vold - m * told;

        list_of_Periodi.push_back(-2.0 * (q / m));
        list_of_Ampiezze.push_back(i);
    }

    std::string filename{"Pendolo_x(Ampiezza)_y(Periodo).png"};
    plt.redirect_to_png(filename);
    plt.plot(list_of_Ampiezze, list_of_Periodi, "", Gnuplot::LineStyle::LINESPOINTS);

    plt.set_xlabel("Ampiezza [m]");
    plt.set_ylabel("Tempo [s]");
    plt.show();

    return 0;
}
