#include <array>
#include <vector>
#include <iostream>
#include <cassert>
#include "fmtlib.h"
#include "gplot++.h"
#include "RandomGen.h"
#include "Esperimento.h"
#include <fstream>
#include <string>

using namespace std;
using namespace fmt;

double media(vector<double> data)
{
    double media{};

    for (int i = 0; i < ssize(data); i++)
    {
        media += data[i];
    }
    double val = double(media / ssize(data));
    return val;
}

double deviazione(vector<double> data, double media)
{
    double varianza = 0;
    for (int k = 0; k < data.size(); k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = double(varianza / (data.size()-1));
    return (varianza);
}

double correlazione(vector<double> a, vector<double> b, vector<double> ab)
{
    return (media(ab) - media(a) * media(b)) / sqrt((deviazione(a, media(a)) * deviazione(b, media(b))));
}

void plot(vector<double> dev1, vector<double> dev2, Gnuplot &scatter)
{
    scatter.set_xlabel("Variabile X");
    scatter.set_ylabel("Variabile Y");
    scatter.histogram(dev1, 100);
    scatter.show();
    scatter.histogram(dev2, 100);
    scatter.show();
    scatter.plot(dev1, dev2, "", Gnuplot::LineStyle::POINTS);
    scatter.show();
}

int main(int argc, char *argv[])
{
    const int N = 10000;

    vector<int> num_of_points{100, 500, 1000, 5000, 10000, 50000, 100000};
    unsigned int seed = 1;
    EsperimentoPrisma experiment(seed);
    // angoli
    vector<double> theta0(N), theta1(N), theta2(N);
    // deviazioni
    vector<double> dev1(N), dev2(N), productdev(N);
    // indice rifrazione
    vector<double> n1(N), n2(N), productn(N);
    // A e B
    vector<double> A(N), B(N), productAB(N);

    Gnuplot plot1{}, plot2{}, plot3{}, plot4{};
    plot1.redirect_to_png("Immagini/Theta.png", "1600, 1000");
    plot2.redirect_to_png("Immagini/Dev.png", "1600,  1000");
    plot3.redirect_to_png("Immagini/N.png", "1600,  1000");
    plot4.redirect_to_png("Immagini/AB.png", "1600,  1000");
    plot1.multiplot(1, 3);
    plot2.multiplot(1, 3);
    plot3.multiplot(1, 3);
    plot4.multiplot(1, 3);

    for (int i = 0; i < 10000; i++)
    {
        experiment.esegui();
        experiment.analizza();
        theta0.at(i) = (experiment.get_theta0_casuale());
        theta1.at(i) = (experiment.get_theta1_casuale());
        theta2.at(i) = (experiment.get_theta2_casuale());
        dev1.at(i) = (experiment.get_Dev1_casuale());
        dev2.at(i) = (experiment.get_Dev2_casuale());
        productdev.at(i) = experiment.get_Dev1_casuale() * experiment.get_Dev2_casuale();
        n1.at(i) = (experiment.get_N1_casuale());
        n2.at(i) = (experiment.get_N2_casuale());
        productn.at(i) = experiment.get_N1_casuale() * experiment.get_N2_casuale();
        A.at(i) = (experiment.get_A_casuale());
        B.at(i) = (experiment.get_B_casuale());
        productAB.at(i) = experiment.get_A_casuale() * experiment.get_B_casuale();
    }
    fmt::println("\n-------------------------------------------------------------------- theta0 - theta1 - theta2--------------------------------------------------------------------");
    fmt::println("Media theta0 = {:4f}, deviazione = {:4f}", media(theta0), sqrt(deviazione(theta0, media(theta0))));
    fmt::println(" Media theta1= {:4f}, deviazione = {:4f}", media(theta1), sqrt(deviazione(theta1, media(theta1))));
    fmt::println(" Media theta2 = {:4f}, deviazione = {:4f}", media(theta2), sqrt(deviazione(theta2, media(theta2))));


    fmt::println("\n-------------------------------------------------------------------- dev1 e dev2 --------------------------------------------------------------------");
    fmt::println(" \nMedia Dev1 = {:4f}, deviazione = {:4f}", media(dev1), sqrt(deviazione(dev1, media(dev1))));
    fmt::println(" Media Dev 2 = {:4f}, deviazione = {:4f}", media(dev2), sqrt(deviazione(dev2, media(dev2))));
    fmt::println(" coeff correlazione dev1 e dev2 = {:4f}%", (100. * correlazione(dev1, dev2, productdev)));
        
    fmt::println("\n-------------------------------------------------------------------- N1 e N2 --------------------------------------------------------------------");
    fmt::println("\nMedia N1 = {:4f}, deviazione = {:4f}", media(n1), sqrt(deviazione(n1, media(n1))));
    fmt::println(" Media N2 = {:4f}, deviazione = {:4f}", media(n2), sqrt(deviazione(n2, media(n2))));
    fmt::println(" coeff correlazione n1 e n2 = {:4f}%", (100. * correlazione(n1, n2, productn)));



    fmt::println("\n-------------------------------------------------------------------- A e B --------------------------------------------------------------------");
    fmt::println("Media A = {:4f}, deviazione = {:4f}", media(A), sqrt(deviazione(A, media(A))));
    fmt::println(" Media B = {} nm^2, deviazione = {} nm^2", media(B)*1E18, sqrt(deviazione(B, media(B)))*1E18);
    fmt::println(" coeff correlazione A e B = {:4f}%", (100. * correlazione(A, B, productAB)));

    plot1.set_xlabel("Variabile X");
    plot1.set_ylabel("Variabile Y");
    plot1.set_title("Theta0");
    plot1.histogram(theta0, 100);
    plot1.show();
    plot1.set_title("Theta1");
    plot1.histogram(theta1, 100);
    plot1.show();
    plot1.set_title("Theta2");
    plot1.histogram(theta2, 100);
    plot1.show();

    plot(dev1, dev2, plot2);
    plot(n1, n2, plot3);
    plot(A, B, plot4);

    return 0;
}
