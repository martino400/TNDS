#pragma once
#include <array>
#include <iostream>
#include <cassert>
#include <array>

using namespace std;

template <typename T, size_t N>
inline array<T, N> operator+(const array<T, N> &a, const array<T, N> &b) // somma tra vettori
{
    array <T, N> risultato;
    for (int i = 0; i < N; i++)
    {
        risultato [i] = a[i] + b[i];
    }
    return risultato;
}


template <typename T, size_t N>
inline array<T, N> operator-(const array<T, N> &a, const array<T, N> &b) // differenza tra vettori
{
    array <T, N> risultato;
    for (int i = 0; i < N; i++)
    {
        risultato [i] = a[i] - b[i];
    }
    return risultato;
}

template <typename T, size_t N>
inline std::array<T, N> operator*(const array<T, N> &a, const array<T, N> &b) // prodotto scalare
{
    array<T, N> risultato;
    for (int i = 0; i < a.size(); i++)
    {
        risultato = risultato + a[i]*b[i];
    }
    return risultato;
}

template <typename T, size_t N>
inline std::array<T, N> operator*(const array<T, N> &a, double b) // prodotto per uno scalare
{
    array<T, N> risultato{};
    for (int i = 0; i < a.size(); i++)
    {
        risultato[i] = b*a[i];
    }
    return risultato;
}

template <typename T, size_t N>
inline std::array<T, N> operator/(const array<T, N> &a, const array<T, N> &b) // divisione tra vettori
{
    for (int i = 0; i < a.size(); i++)
    {
        a[i]/b[i];
    }
}

// cerco x(0 + h) e espando con taylor e lo approssimo con x(0) + h*x