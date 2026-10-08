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
    test_rg();
    test_euler();
    test_operations();
    if (argc != 2)
    {
        fmt::println("Problema su come è stato eseguito il programma! Devi inserire <eseguibile> e <grandezza passo>");
        exit(-1);
    }

    // for starters...

    RungeK<double, 4> rgk;

    Gravita terra(1.989e+30);

    //COMPLICATO, DEVO LAVORARE SIA CON X CHE CON Y

    // tempi...

    const double tmax{12.0};
    const double h{stof(argv[1])};
    double t{};
    int num_of_steps{(int)lround(tmax / h)};

    vector<double> list_of_x;
    vector<double> list_of_y;

    // SISTEMA TERRA-SOLE da capire
    Gnuplot plt{};
    array<double, 4> x{1000000.0, 0.0, 1000.0, 0.0};
    for (int step = 0; step < num_of_steps; step++)
    {
        x = rgk.Passo(t, x, h, terra);
        t = t + h;
        list_of_x.push_back(x[0]);
        list_of_y.push_back(x[2]);
    }

    std::string filename1{"Terra-sole.png"};
    plt.redirect_to_png(filename1);
    plt.plot(list_of_x, list_of_y);
    plt.set_xlabel("X [m]");
    plt.set_ylabel("Y [m]");
    plt.show();


    return 0;
}
