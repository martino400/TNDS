#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <cassert>
#include "VectorOperations.h"
#include "fmtlib.h"
#include "FunzioneVettoriale.h"
#include "gplot++.h"

using namespace std;

//inizializzare sempre gli array usando
//std::array in modo da avere sempre il controllo 
//sulla dimensione dell'array NON E' SCONTATO

void test_operations()
{
    std::array x{1.0, 2.0, 3.0};
    std::array y{2.0, 1.0, 0.0};
    std::array<double, 3> z, z1;
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
    test_euler();
    test_operations();
    if (argc != 2)
    {
        fmt::println("Problema su come è stato eseguito il programma! Devi inserire <eseguibile> e <grandezza passo>");
        exit(-1);
    }

    Eulero<double, 2> euler;

    OscillatoreArmonico osc(1.0);

    const double tmax{70.};
    const double h{stof(argv[1])};
    double t{};

    array<double, 2> x{0.0, 1.0};

    int num_of_steps{(int)lround(tmax / h)};

    Gnuplot plt{};

    std::vector<double> list_of_t(num_of_steps);
    std::vector<double> list_of_x(num_of_steps);
    std::vector<double> list_of_v(num_of_steps);

    for (int step = 0; step < num_of_steps; step++)
    {
        // Salva le coordinate del punto (t, x)
        list_of_t.push_back(t);
        list_of_x.push_back(x[0]);
        list_of_v.push_back(x[1]);

        // Stampa i risultati in forma di tabella
        fmt::println("Tempo = {:.1f}, Posizione = {:.6f}, Velocita = {:.6f}", t, x[0], x[1]);

        // “Avanza” di un passo `h` la soluzione in `x`
        x = euler.Passo(t, x, h, osc);
        t = t + h;
    }
    fmt::println("Plot rosa = posizione, Plot verde = velocità");

    std::string filename{"euler.png"};
    plt.redirect_to_png(filename);
    plt.plot(list_of_t, list_of_x);
    plt.plot(list_of_t, list_of_v);

    plt.set_xlabel("Tempo [s]");
    plt.set_ylabel("Oscillazione [m]");
    plt.show();

    fmt::println("Finito, il risultato è nel grafico '{}'", filename);

    Gnuplot plt1{};

    std::vector<double> list_of_pass; // sulle x
    std::vector<double> list_of_err;  // sulle y
    double err = 0.0;

    std::vector<double> tempo; // tempo

    // DEVO FARE GRAFICO ERRORE - PASSO INTEGRAZIONE;
    for (double pass = 0.00001; pass <= 0.1001; pass += 0.001)
    {
        t = 0.0;
        num_of_steps = {(int)lround(tmax / pass)};
        cout << num_of_steps << endl;
        array<double, 2> c{0.0, 1.0};
        for (int step = 0; step < num_of_steps; step++)
        {
            c = euler.Passo(t, c, pass, osc);
            if (step == num_of_steps - 1)
            {
                err = fabs(sin(osc.getOmega() * t) - c[0]);
            }
            t = t + pass;
        }
        fmt::println("Errore = {:.6f}, Passo= {:.6f} ", err, pass);
        list_of_err.push_back(err);
        list_of_pass.push_back(pass);
        err = 0.0;
    }

    std::string filename1{"erroriRungeKutta.png"};
    plt1.redirect_to_png(filename1);
    plt1.plot(list_of_pass, list_of_err);
    plt1.set_logscale(Gnuplot::AxisScale::LOGXY);
    plt1.set_xlabel("Passo integrazione [m]");
    plt1.set_ylabel("Errori [m]");
    plt1.show();
    fmt::println("Finito, il risultato è nel grafico '{}'", filename1);



    return 0;
}
