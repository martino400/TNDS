#include <iostream>
#include <string>
#include "funzionebase.h"
#include "fmtlib.h"
#include <cassert>
#include <numbers>
#include "integral.h"
#include "gplot++.h"
#define _USE_MATH_DEFINES

using namespace std;
using namespace fmt;


bool are_close(double calculated, double expected, double epsilon = 1e-9) {
    return std::fabs(calculated - expected) < epsilon;
}

void test_midpoint() {
    xsinx xsinx{};
    midpoint mp{};
    simpson sp{};
    trapezio trap{};

    // Test delle integrazioni utilizzando assert e are_close
    assert(are_close(mp.integrate(0, M_PI / 2, 10, xsinx), 0.9989696941917652));
    assert(are_close(mp.integrate(0, M_PI / 2, 100, xsinx), 0.999989718940119));
    assert(are_close(mp.integrate(M_PI / 2, 0, 10, xsinx), -0.998969694191765));
    assert(are_close(mp.integrate(0, 1, 10, xsinx), 0.3005925674684609));
    assert(are_close(mp.integrate(1, 2, 30, xsinx), 1.440482828731412));

    assert(are_close(sp.integrate(0, M_PI / 2, 10, xsinx), 0.9999898033639686));
    assert(are_close(sp.integrate(0, M_PI / 2, 100, xsinx), 0.9999999989852724));


    assert(are_close(trap.integrate(0, M_PI / 2, 10, xsinx), 1.0020587067645337));
    assert(are_close(trap.integrate(0 , M_PI / 2, 100, xsinx), 1.0000205619295077));
    assert(are_close(trap.integrate(0, 1, 10, xsinx), 0.30232058249393656));
    assert(are_close(trap.integrate(1, 2, 30, xsinx), 1.4403016069813432));    

    std::cerr << "The midpoint function works correctly! 🥳\n";
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Errore con il programma, numero sbagliato di argomenti da inserire, inserire <eseguibile> e <n di passi>!!" << endl;
        return -1;
    }

    test_midpoint();

    int nstep{stoi(argv[1])};

    xsinx func{};

    simpson i{};

    double valore{i.integrate(0, M_PI, nstep, func)};

    double precisione = 1.0 / nstep;

    fmt::println("N step = {} ; valore integrale = {} ; precisione = {}", nstep, valore, precisione);

    simpson myInt{};

    std::vector<int> steps{10, 50, 100, 500, 1000, 2000, 10000, 50000, 100000, 1000000};
    std::vector<double> step_sizes(size(steps));
    std::vector<double> errors(size(steps));

    // Calcola gli errori e stampa una tabella usando "fmtlib.h"
    double true_value{M_PI};
    fmt::println("Passi        Intervallo h  Errore");

    for (int i = 0; i < size(steps); i++)
    {
        errors[i] = abs(true_value - myInt.integrate(0, M_PI, steps[i], func));
        step_sizes[i] = myInt.getH(); //da ricordare che posso usare GETH solo dopo aver fatto integrate
        fmt::println("{:12d} {:14.8e} {:20.8e}", steps[i], step_sizes[i], errors[i]);
    }

    // Crea un plot
    Gnuplot plt{};
    const string output_file_name{"./Immagini/SIMPSON-error1.png"};
    plt.redirect_to_png(output_file_name, "800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGXY);
    plt.plot(step_sizes, errors);
    plt.set_xlabel("Passo di integrazione h");
    plt.set_ylabel("Errore");
    plt.show();
    // È sempre consigliato fornire un messaggio all'utente
    // per comunicare che è stato salvato un plot. Includete
    // sempre il nome del file nel messaggio!
    fmt::println("Plot saved in '{}'", output_file_name);

    return 0;
}
