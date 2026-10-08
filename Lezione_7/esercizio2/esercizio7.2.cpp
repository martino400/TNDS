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

bool are_close(double calculated, double expected, double epsilon)
{
    return std::fabs(calculated - expected) < epsilon;
}

void test_trapezio()
{
    xsinx xsinx{};
    trapezio mp{};

    // Test delle integrazioni utilizzando assert e are_close
    assert(are_close(mp.int_prec(0, M_PI / 2, 0.1, xsinx), 1.0129507467218792, 0.1));
    assert(are_close(mp.int_prec(0, M_PI / 2, 0.01, xsinx), 1.0008035776793722, 0.01));
    assert(are_close(mp.int_prec(M_PI / 2, 0, 1.0e-5, xsinx), -1.0000007843660552, 1.0e-5));
    std::cerr << "The trapezoid function works correctly! 🥳\n";
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Errore con il programma, numero sbagliato di argomenti da inserire, devi inserire <eseguibile> e <precisione>!!" << endl;
        cout << "Inserisci eseguibile" << endl;
        return -1;
    }
    test_trapezio();

    double prec{stod(argv[1])};

    xsinx func{};

    trapezio myInt{};

    // integro sulla precisione
    double valore{myInt.int_prec(0, M_PI, prec, func)};
    std::vector<int> steps{10, 50, 100, 500, 1000};
    std::vector<double> step_sizes(size(steps));
    std::vector<double> errors(size(steps));

    // Calcola gli errori e stampa una tabella usando "fmtlib.h"
    double true_value{M_PI};
    fmt::println("Passi        Intervallo h  Errore");

    for (int i = 0; i < size(steps); i++)
    {
        errors[i] = abs(true_value - myInt.integrate(0, M_PI, steps[i], func));
        step_sizes[i] = myInt.getH(); // da ricordare che posso usare GETH solo dopo aver fatto integrate
        fmt::println("{:12d} {:14.8e} {:20.8e}", steps[i], step_sizes[i], errors[i]);
    }

    // Crea un plot
    Gnuplot plt{};
    const string output_file_name{"./Immagini/TRAPEZIO-error1.png"};
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

    int npassi;
    fmt::println("Quanti passi vuoi fare??");
    cin >> npassi;

    // integro sui passi
    double valore1{myInt.integrate(0, M_PI, npassi, func)};

    fmt::println("Valore integrale = {} ; precisione = {}, intregrale tra {} e {}", valore, prec, 0, M_PI);
    fmt::println("Valore integrale = {} ; npassi = {}, intregrale tra {} e {}", valore1, npassi, 0, M_PI);

    return 0;
}
