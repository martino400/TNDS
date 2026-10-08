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

vector<double> ParseFile(string filename);
double funzione(double q, vector<double> params);
double deriv(double qmin, vector<double> params);
template <typename T>
double mean(const vector<T> &v, int stride);
template <typename T>
double stddev(const vector<T> &v, int stride);


template <typename T>
vector <T> derivata(const vector<T> &v, int stride);

// IMPLEMENTAZIONE
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<double> ParseFile(string filename)
{
    vector<double> v;
    ifstream in{filename.c_str()};
    double val;
    while (in >> val)
    {
        v.push_back(val);
    }
    in.close();
    return v;
}

// Svolto s(q)
double funzione(double q, vector<double> Q)
{
    double sum{};
    for (int i = 0; i < ssize(Q); i++)
    {
        sum += pow((Q[i] / round(Q[i] / q) - q), 2);
    }

    return sum;
}

// Svolto qmin

double deriv(double qmin, vector<double> params)
{
    double sum{};
    for (int k{}; k < ssize(params); k++)
        sum += (params[k] / round(params[k] / qmin));
    return sum / ssize(params); 
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

template <typename T>
vector <T> derivata(const vector<T> &v, int stride)
{
    for(int i=0; i<ssize(v); i++)
    {

    }

}

