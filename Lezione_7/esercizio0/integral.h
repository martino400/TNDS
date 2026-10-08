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
        m_h = (m_b - m_a) / step;
        double a{}, sum{};

        for (int i = 0; i <= step; i++)
        {
            if (i == 0 || i == step)
            {
                sum += (f.eval(a)) / 3;
            }
            if (i % 2 != 0)
            {
                sum += 4 * (f.eval(a)) / 3;
            }
            if (i % 2 == 0)
            {
                sum += 2 * (f.eval(a)) / 3;
            }
            a = (m_a + i * m_h);
        }

        return sum * m_h;
    }
    double integrate_prec(double prec, const funzionebase &f) override {};
};

// classe FIGLIA, astratta

class trapezio : public integral
{
public:
    trapezio() : integral() {};

protected:
    double calculate(int nstep, const funzionebase &f) override
    {
        double m_h = (m_b - m_a) / nstep;
        double a{m_a};
        double somma1{f.eval(m_a)+f.eval(m_b)},sum{somma1};;
        for (int i = 0; i <= nstep; i++)
        {
            if(i!= 0 || i!=nstep)
            {
                sum += (f.eval(a));
            }
            a = (m_a + i * m_h);
        }
        return sum * m_h;
    }
    double integrate_prec(double prec, const funzionebase &f) override
    {
        double sc{}, pr{1};
        int n{2};
        do
        {
            sc = pr; //in questo modo non devo calcolare 2 integrali diversi. 
            pr = calculate(n/2, f);
            n*=2;
        } while (prec<fabs(sc-pr)*(4.0)/(3.0));
        fmt::println("Numero di iterazioni ={}", n);
        return sc;
    }
};