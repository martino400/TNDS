#pragma once
#include <array>
#include <iostream>
#include <cassert>
#include <array>
#include <cmath>
#include "VectorOperations.h"

template <typename T, size_t N>
class FunzioneVettorialeBase
{
public:
    virtual ~FunzioneVettorialeBase() {};
    virtual array<T, N> eval(double x, const array<T, N> &a) const = 0;
};

// oscillatore armonico a una dimensione ossia a 2 dimensioni nello spazio delle fasi
//  lo spazio delle fasi è composto da x(t) e v(t)
// prima componente dell'array x
// seconda componente dell'array v
class OscillatoreArmonico : public FunzioneVettorialeBase<double, 2>
{
public:
    OscillatoreArmonico(double omega) { m_omega = omega; }
    array<double, 2> eval(double t, const array<double, 2> &a) const override
    {
        array<double, 2> risultato{};
        risultato[0] = a[1];                      // x
        risultato[1] = (-pow(m_omega, 2)) * a[0]; // v
        return risultato;
    }
    double getOmega() const { return m_omega; }

private:
    double m_omega;
};

class Gravita : public FunzioneVettorialeBase<double, 4>
{
public:
    Gravita(double Massa) { m_massa = Massa; }
    array<double, 4> eval(double t, const array<double, 4> &a) const override
    {
        const double G = 6.67430e+10;
        array<double, 4> risultato{};
        risultato[0] = a[1];                    // x_x
        risultato[1] = -(G * m_massa) / (a[0]); // v_x

        risultato[0] = a[1];                    // x_y
        risultato[1] = -(G * m_massa) / (a[2]); // v_y
        return risultato;
    }
    double getMassa() const { return m_massa; }

private:
    double m_massa;
};

// Prima l'avevo fatto come l'oscillatore armonico, sbagliato
class Pendolo : public FunzioneVettorialeBase<double, 2>
{
public:
    Pendolo(double lunghezza, double gravitazione)
    {
        m_lunghezza = lunghezza;
        m_gravitazione = gravitazione;
    }
    array<double, 2> eval(double t, const array<double, 2> &a) const override
    {
        array<double, 2> risultato{};
        risultato[0] = a[1];                                            // x
        risultato[1] = (-(m_gravitazione / m_lunghezza) * (sin(a[0]))); // v
        return risultato;
    }

private:
    double m_lunghezza;
    double m_gravitazione;
};

class OscillatoreForzato : public FunzioneVettorialeBase<double, 2>
{
public:
    OscillatoreForzato(double omega, double alfa, double omegaf)
    {
        m_omega = omega;
        m_alfa = alfa;
        m_omegaf = omegaf;
    }
    array<double, 2> eval(double t, const array<double, 2> &a) const override
    {
        array<double, 2> risultato{};
        risultato[0] = a[1];                                                                // x
        risultato[1] = (-pow(m_omega, 2)) * a[0] - m_alfa * a[1] + 1.0 * sin(m_omegaf * t); // v
        return risultato;
    }
    double getOmega() const { return m_omega; }
    double getOmegaf() const { return m_omegaf; }
    double getalfa() const { return m_alfa; }

private:
    double m_omega;
    double m_omegaf;
    double m_alfa;
};

template <typename T, size_t N>
class EquazioneDifferenzialeBase
{
    // passo_h --> passo h
public:
    virtual std::array<double, N>
    Passo(double t, const std::array<double, N> &x, double h,
          const FunzioneVettorialeBase<double, N> &f) const = 0;
};

template <typename T, size_t N>
class Eulero : public EquazioneDifferenzialeBase<double, N>
{
public:
    virtual std::array<double, N>
    Passo(double t, const std::array<double, N> &x, double h,
          const FunzioneVettorialeBase<double, N> &f) const override
    {
        array<double, 2> risultato{};
        risultato = x + (f.eval(t, x) * h);
        return risultato;
    }
};

template <typename T, size_t N>
class RungeK : public EquazioneDifferenzialeBase<double, N>
{
    // f eval mi restituisce xpunto(t, x)
public:
    virtual std::array<double, N>
    Passo(double t, const std::array<double, N> &x, double h,
          const FunzioneVettorialeBase<double, N> &f) const override
    {
        array<double, N> risultato{};
        array<double, N> k1{}, k2{}, k3{}, k4{};
        k1 = f.eval(t, x);
        k2 = (f.eval(t + h / 2, x + (k1 * (h / 2.0))));
        k3 = (f.eval(t + h / 2, x + (k2 * (h / 2.0))));
        k4 = (f.eval(t + h, x + k3 * h));

        risultato = x + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (h / 6.0);
        return risultato;
    }
};
