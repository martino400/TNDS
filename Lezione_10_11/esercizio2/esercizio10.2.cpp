#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <cassert>
#include "fmtlib.h"
#include "gplot++.h"
#include "RandomGen.h"
#include "funzionebase.h"
#include "IntegralMC.h"
#include <fstream>
#include <string>

using namespace std;
using namespace fmt;

//non far andare 10.2 perchè ci mette una vita

int main(int argc, char *argv[])
{
    double fmax(M_PI_2);
    const int N = 10000;

    vector<int> num_of_points{100, 500, 1000, 5000, 10000, 50000, 100000};

    IntegraMedia media(1);
    IntegraHitMiss miss(1);
    xsinx f{};

    for (int i = 0; i < 7; i++)
    {
        ofstream out;
        ofstream out1;
        out.open(fmt::format("Dati10.2/RisultatiIntegraliMedia{}.dat", i + 1));
        out1.open(fmt::format("Dati10.2/RisultatiIntegraliMiss{}.dat", i + 1));
        for (int k = 0; k < N; k++)
        {
            out << media.valore(f, 0, M_PI_2, 0, num_of_points[i]) << endl;
            out1 << miss.valore(f, 0, M_PI_2, fmax, num_of_points[i]) << endl;
        }
        out.close();
        out1.close();
    }


    return 0;
}
