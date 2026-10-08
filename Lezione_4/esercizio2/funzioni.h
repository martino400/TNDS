#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// argc si becca il numero di parametri passati dalla linea di comando
// argv si becca i parametri passati dalla linea di comando
// il primo parametro è sempre il nome dell'eseguibile

using namespace std;

// Dichiarazione
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void ParseFile(string filename, vector<T> &v, vector<T> &rB, vector<T> &error, vector<T> &error1);
double fun(double q, vector<double> params);
double deriv(double qmin, vector<double> params);
template <typename T>
double mean(const vector<T> &v, int stride);
template <typename T>
double stddev(const vector<T> &v, int stride);
template <typename T>
vector<double> mistake(const vector<T> &V, const vector<T> &rB, const vector<T> &error);

// IMPLEMENTAZIONE
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prima colonna:2DeltaV
// Seconda colonna: rB quadro
// Terza colonna: errore su rB quadro

template <typename T>
void ParseFile(string filename, vector<T> &v, vector<T> &rB, vector<T> &error, vector<T> &error1)
{
    ifstream in{filename.c_str()};
    T val, val1, val2, val3;
    while (in >> val >> val1 >> val2 >> val3)
    {
        v.push_back(val);
        rB.push_back(val1);
        error.push_back(val2);
        error1.push_back(val3);
    }
    in.close();
}

// Errore su e/m (NON SERVE)
template <typename T>
vector<double> mistake(const vector<T> &V, const vector<T> &rB, const vector<T> &error)
{
    vector<double> mis;
    for (int i = 0; i < ssize(rB); i++)
    {
        mis.push_back((2 * V(i) * error(i)) / pow(rB(i), 2));
    }
    return mis;
}

template <typename T>
double mean(const vector<T> &v, int stride)
{
    double accum{};
    int n{};
    for (int k{}; k < ssize(v); k += stride, n++)
    { // Nota: Incrementiamo sia k che n!
        accum += v.at(k);
    }
    return accum / n;
}

template <typename T>
double stddev(const vector<T> &v, int stride)
{
    const double m = mean(v, stride);
    double accum{};
    int n{};
    for (int k{}; k < ssize(v); k += stride, n++)
    { // Nota: Incrementiamo sia k che n!
        accum += pow((v[k] - m), 2);
    }
    return sqrt(accum / n);
}

