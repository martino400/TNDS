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

// t va da 0 a 70 secondi
// h compreso tra 0.1 e 0.001 secondi --> meno di 0.001 secondi e ci mette troppo il programma
int main(int argc, char *argv[])
{

    Gnuplot plt{};
    vector<double> list_of_frequency;
    vector<double> list_of_Guadagno;
    ifstream input_file;
    input_file.open("dati.dat");
    while(input_file.eof() == false)
    {
        double x, y;
        input_file >> x >> y;
        fmt::println("x = {}, y = {}", x, y);
        list_of_frequency.push_back(x);
        list_of_Guadagno.push_back(y);
    }

    // for (int i = 0; i < 19; i++)
    // {
    //     fmt::println("list_of_frequency[{}] = {}, list_of_Guadagno[{}] = {}", i, list_of_frequency.at(i), i, list_of_Guadagno.at(i));
    // }

    input_file.close();

    string filename{"Phase.png"};
    plt.redirect_to_png(filename);
    plt.plot(list_of_frequency, list_of_Guadagno, "", Gnuplot::LineStyle::LINESPOINTS);
    plt.set_xlabel("Frequency [1/s]");
    plt.set_ylabel("Phase [rad]");
    plt.set_logscale(Gnuplot::AxisScale::LOGXY);
    // plt.set_xrange(100,15000);
    plt.set_title("Phase Band-Pass Filter");
    plt.show();

    fmt::println("Finito, il risultato è nel grafico '{}'", filename);

    return 0;
}
