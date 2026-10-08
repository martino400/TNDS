#pragma once
#include <iostream>
#include "fmtlib.h"
#include <cmath>
#include "funzionebase.h"

// classe INTEGRAL

class integral
{
public:
    integral() : m_a{}, m_b{}, m_sign{}, m_h{} {};

    double integrate(double a, double b, int nstep, funzionebase &f)
    {
        checkInterval(a, b);
        return m_sign * calculate(nstep, f);
    }

    double int_prec(double a, double b, double precisione, funzionebase &f)
    {
        checkInterval(a, b);
        return m_sign * integrate_prec(precisione, f);
    }

    double getA() { return m_a; }
    double getB() { return m_b; }
    double getsign() { return m_sign; }
    double getH() { return m_h; }
    void setH(double h) { m_h = h; }

protected:
    virtual double calculate(int step, const funzionebase &f) = 0;
    virtual double integrate_prec(double prec, const funzionebase &f) = 0;
    void checkInterval(double a, double b)
    {
        m_a = std::min(a, b);
        m_b = std::max(a, b);
        if (b > a)
        {
            m_sign = 1.0;
        }
        else if (b < a)
        {
            m_sign = -1.0;
        }
    }

    double m_a, m_b;
    double m_sign;
    double m_h;
};

// classe FIGLIA, astratta

class midpoint : public integral
{
public:
    midpoint() : integral() {};

protected:
    double calculate(int step, const funzionebase &f) override
    {
        double midpoint{}, valore{};
        m_h = (m_b - m_a) / step;
        for (int i = 0; i < step; i++)
        {
            midpoint = (m_a + (i + 0.5) * m_h);
            valore = valore + f.eval(midpoint) * m_h; // calcolo area del rettangolo
            // assegno i nuovi valori una volta finito il ciclo
        }
        return valore;
    }
    double integrate_prec(double prec, const funzionebase &f) override {};
};

// classe FIGLIA, astratta

class simpson : public integral
{
public:
    simpson() : integral() {};

protected:
    double calculate(int step, const funzionebase &f) override
    {
        // Aggiusta il numero di passi per assicurarti che sia pari
        int truen = step;
        if (step % 2 != 0)
        {
            truen = step + 1;
        }

        // Calcolo della larghezza dei sottointervalli
        m_h = (m_b - m_a) / truen;

        // Inizializza l'accumulatore con i contributi di f(m_a) e f(m_b)
        double acc = (1.0 / 3.0) * (f.eval(m_a) + f.eval(m_b));

        // Ciclo per calcolare il contributo degli altri termini
        for (int k = 1; k < truen; ++k)
        {
            double x_k = m_a + k * m_h; // Calcola il punto corrente
            acc += (2.0 / 3.0) * (1 + k % 2) * f.eval(x_k);
        }

        // Ritorna il risultato finale moltiplicato per m_h
        return acc * m_h;
    }

    double integrate_prec(double prec, const funzionebase &f) override {};
};

// classe FIGLIA, astratta

class trapezio : public integral
{
public:
    trapezio() : integral() {};

protected:
    double calculate(int step, const funzionebase &f) override
    {
        // Calcolo della larghezza dei sottointervalli
        m_h = (m_b - m_a) / step;

        // Inizializza l'accumulatore con i contributi di f(m_a) e f(m_b)
        double acc = (f.eval(m_a) + f.eval(m_b)) / 2.0;

        // Ciclo per calcolare il contributo degli altri punti
        for (int k = 1; k < step; ++k)
        {
            double x_k = m_a + k * m_h; // Calcola il punto corrente
            acc += f.eval(x_k);         // Aggiungi il contributo del punto interno
        }

        // Ritorna il risultato finale moltiplicato per m_h
        return acc * m_h;
    }

    double integrate_prec(double prec, const funzionebase &f) override
    {
        double sc{}, pr{1};
        int n{2};
        do
        {
            sc = pr; // in questo modo non devo calcolare 2 integrali diversi.
            pr = calculate(n / 2, f);
            n *= 2;
        } while (prec < fabs(sc - pr) * (4.0) / (3.0));
        fmt::println("Numero di iterazioni ={}", n);
        return sc;
    }
};