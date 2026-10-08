#include <iostream>
#include <fstream>
#include <string>
#include "CampoVettoriale.h"
#include "PuntoMateriale.h"
#include <cassert>
#include "gplot++.h"

#include "fmtlib.h"

using namespace std;
using namespace fmt;
bool are_close(double calculated, double expected, double epsilon = 1e-7);

void test_coordinates(void);

void test_coulomb_law(void);

int main(int argc, char *argv[])
{
    const double e{1.60217653E-19};
    const double me{9.1093826E-31};
    const double mp{1.67262171E-27};
    const double d{1.e-10};
    //assert 
    test_coordinates();
    test_coulomb_law();
    if (argc != 4)
    {
        cerr << "Errore con il programma, inserire <eseguibile> ;  <x>,  <y>, e <z>" << endl;
        exit(1);
    }

    // for(auto i=0; i<1000000; i++)
    // {
    //     //smart pointers, dealloca da solo quando va fuori dallo scope
    //     unique_ptr<particella> p = make_unique<particella> (i, 100*i);
    //     cout << "stiamo a vedere" << endl;
    // }
    double x{stod(argv[1])};
    double y{stod(argv[2])};
    double z{stod(argv[3])};

    posizione p(x, y, z);

    PuntoMateriale protone(mp, e, 0, 0, -d / 2);
    PuntoMateriale elettrone(me, -e, 0, 0, d / 2);


    CampoVettoriale E{elettrone.CampoElettrico(p) + protone.CampoElettrico(p)};

    cout << "Modulo di E = " << E.Modulo() << endl; // è giusto funziona
    fmt::println("Ex = {},  Ey = {},  Ez = {}", E.getFx(), E.getFy(), E.getFz()); //coordinate del campo

    vector<double> distanza; //faccio approssimazione per cui il dipolo diventa un punto unico, io mi sposto sulle z e il dipolo è collocato sulle z
    vector<double> campo;
    for (double q = 100 * d; q < 1000 * d; q += 10 * d)
    {
        distanza.push_back(q * 1.e+9); // faccio per 10^-9 per salvarlo in nm e non metri
        posizione pos{0, 0, q};
        CampoVettoriale E{elettrone.CampoElettrico(pos) + protone.CampoElettrico(pos)};
        campo.push_back(E.Modulo());
        // fmt::println("{},{}", modulo[i], campo[i]);
    }

    //plot dell'andamento
    Gnuplot plt{};
    plt.redirect_to_png("Immagini/Andamento_Campo.png");
    plt.multiplot(1, 1, "Esercizio 5");


    plt.set_logscale(Gnuplot::AxisScale::LOGXY); //scala bilogaritmica
    plt.set_xlabel("Distance [nm]");
    plt.set_ylabel("Electric field [N/C]");

    plt.plot(distanza, campo);

    // Ricordarsi di chiamarlo, altrimenti il grafico non verrà salvato/visualizzato
    plt.show();

    return 0;
}

bool are_close(double calculated, double expected, double epsilon)
{
    return fabs(calculated - expected) < epsilon;
}

void test_coordinates(void)
{
    posizione p{1, 2, 3};

    assert(are_close(p.getX(), 1.0));
    assert(are_close(p.getY(), 2.0));
    assert(are_close(p.getZ(), 3.0));

    assert(are_close(p.getR(), 3.7416573867739));
    assert(are_close(p.getPhi(), 1.1071487177941));
    assert(are_close(p.getTheta(), 0.64052231267943));
    assert(are_close(p.getRho(), 2.2360679774998));

    cerr << "The coordinates work correctly! 🥳\n";
}

void test_coulomb_law(void)
{
    // 0.5 µC charge with no mass (irrelevant for the electric field)
    PuntoMateriale particella1{0.0, 5e-7, 5, 3, -2};
    posizione p{-2, 4, 1};

    CampoVettoriale V{particella1.CampoElettrico(p)};

    assert(are_close(V.getFx(), -69.41150052142065));
    assert(are_close(V.getFy(), 9.915928645917235));
    assert(are_close(V.getFz(), 29.747785937751708));

    cerr << "Coulomb's law works correctly! 🥳\n";
}