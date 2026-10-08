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
    if (argc != 2)
    {
        fmt::println("Problema su come è stato eseguito il programma! Devi inserire <eseguibile> e <grandezza passo>");
        exit(-1);
    }

    // for starters...

    RungeK<double, 2> rgk;

    OscillatoreForzato forzato1(10.0, 1.0 / 30.0, 10.0);
    //OscillatoreForzato forzato (omega, alfa, omega_della_forzante)


    // tempi...

    const double tmax{300.0};
    const double h{stof(argv[1])};
    double t{};
    int num_of_steps{(int)lround(tmax / h)};

    vector<double> list_of_tempi;
    vector<double> list_of_posizione;

    // SISTEMA FORZATO CON OMEGA F = OMEGA SISTEMA
    Gnuplot plt{};
    array<double, 2> x{0.0, 0.0};
    for (int step = 0; step < num_of_steps; step++)
    {
        x = rgk.Passo(t, x, h, forzato1);
        t = t + h;
        list_of_posizione.push_back(x[0]);
        list_of_tempi.push_back(t);
    }

    std::string filename1{"Immagini/Sistemaforzato.png"};
    plt.redirect_to_png(filename1);
    plt.plot(list_of_tempi, list_of_posizione);
    plt.set_xlabel("Tempo [s]");
    plt.set_ylabel("Posizione [m]");
    plt.show();

    // LORENTIANA
    Gnuplot plt1{};
    double max{};

    std::vector<double> list_of_omegaf;
    std::vector<double> Ampiezze;

    for (double omega_f{9.05}; omega_f <= 11.01; omega_f += 0.01)
    {
        max = 0;
        OscillatoreForzato forzato2(10.0, (1.0 / 30.0), omega_f);
        array<double, 2> x{0.0, 0.0};
        t = 0;
        for (int step = 0; step < num_of_steps; step++)
        {
            x = rgk.Passo(t, x, h, forzato2);
            t = t + h;
            if (t > (tmax-30.0)) // a trenta secondi dalla fine, per la relazione sui battimenti
            {
                if (max < x[0])
                {
                    max = x[0];
                }
            }
        }
        fmt::println(" omega = {}    max = {}", omega_f, max);
        list_of_omegaf.push_back(omega_f);
        Ampiezze.push_back(max);
    }

    std::string filename{"Immagini/Lorentziana.png"};
    plt1.redirect_to_png(filename);
    plt1.plot(list_of_omegaf, Ampiezze);

    plt1.set_xlabel("Pulsazione [s]");
    plt1.set_ylabel("Ampiezza [m]");
    plt1.show();

    return 0;
}
