#pragma once
#include <iostream>
#include "RandomGen.h"
#include <cmath>
using namespace std;
class EsperimentoPrisma
{
public:
    EsperimentoPrisma(unsigned int seed);
    ~EsperimentoPrisma() {};
    void esegui();
    void analizza();

    double get_A_casuale() { return m_Acas; };
    double get_B_casuale() { return m_Bcas; };
    double get_N1_casuale() { return m_n1cas; };
    double get_N2_casuale() { return m_n2cas; };
    double get_Dev1_casuale() { return m_dev1cas; };
    double get_Dev2_casuale() { return m_dev2cas; };
    double get_theta0_casuale() { return m_theta0cas; };
    double get_theta1_casuale() { return m_theta1cas; };
    double get_theta2_casuale() { return m_theta2cas; };

protected:
    RandomGen m_random;
    // parametri dell'apparato

    double m_lambda1, m_lambda2, m_alpha, m_sigmat;

    // cas = valore assunto dalla simulazione (casuale)
    // input = valore assunto perchè ce l'ho messo io per ottere A e B iniziali

    double m_theta0input, m_theta0cas;
    double m_theta1input, m_theta1cas;
    double m_theta2input, m_theta2cas;
    double m_dev1input, m_dev1cas;
    double m_dev2input, m_dev2cas;
    double m_Ainput, m_Acas;
    double m_Binput, m_Bcas;
    double m_n1input, m_n1cas;
    double m_n2input, m_n2cas;
};

// alpha ricordo che è l'angolo del prisma
// sigmat è l'errore con cui prendo i dati, ossia sigma_theta

EsperimentoPrisma::EsperimentoPrisma(unsigned int seed) : m_random(seed),
                                                          m_lambda1(579.1E-9),
                                                          m_lambda2(404.E-9),
                                                          m_alpha(double(M_PI / 3.0)),
                                                          m_sigmat(0.3E-3),
                                                          m_Ainput(2.7),
                                                          m_Binput(60000E-18)
{
    // indici di rifrazione attesi
    m_n1input = sqrt(m_Ainput + m_Binput / (m_lambda1 * m_lambda1));
    m_n2input = sqrt(m_Ainput + m_Binput / (m_lambda2 * m_lambda2));

    m_theta0input = (M_PI_2);

    // determino theta1 e theta2

    m_dev1input = 2.0 * asin(m_n1input * sin(double(m_alpha * 0.5))) - m_alpha;
    m_dev2input = 2.0 * asin(m_n2input * sin(double(m_alpha * 0.5))) - m_alpha;

    m_theta1input = m_dev1input + m_theta0input;
    m_theta2input = m_dev2input + m_theta0input;
}

void EsperimentoPrisma::esegui()
{
    // faccio le misure
    m_theta0cas = m_random.GaussBOXMULLER(m_theta0input, m_sigmat);
    m_theta1cas = m_random.GaussBOXMULLER(m_theta1input, m_sigmat);
    m_theta2cas = m_random.GaussBOXMULLER(m_theta2input, m_sigmat);
}

void EsperimentoPrisma::analizza()
{
    // calcolo deviazione minima
    m_dev1cas = get_theta1_casuale() - get_theta0_casuale();
    m_dev2cas = get_theta2_casuale() - get_theta0_casuale();
    // cerr << get_theta2_casuale() - get_theta0_casuale()<< endl;

    // calcolo n
    m_n1cas = sin((m_dev1cas + m_alpha) / 2.0) / sin(m_alpha / 2.0);

    m_n2cas = sin((m_dev2cas + m_alpha) / 2.0) / sin(m_alpha / 2.0);

    // calcolo di A e B

    m_Acas = ((m_lambda2 * m_lambda2) * (m_n2cas * m_n2cas) - (m_lambda1 * m_lambda1) * (m_n1cas * m_n1cas)) / ((m_lambda2 * m_lambda2) - ((m_lambda1 * m_lambda1)));
    m_Bcas = ((m_n2cas * m_n2cas) - (m_n1cas * m_n1cas)) / ((1 / (m_lambda2 * m_lambda2)) - (1 / (m_lambda1 * m_lambda1)));
}

class PianoInclinato
{
public:
    PianoInclinato(unsigned int seed);
    ~PianoInclinato() {};
    void esegui();
    void analizza();
    double get_g() { return g_cas; }

    void setErroreL(double errore) { errore_L = errore; }
    void setErroreTheta(double errore) { errore_theta = errore; }
    void setErroreT(double errore) { errore_t = errore; }
    void setAngolo(double angolo) { theta = angolo; }

protected:
    RandomGen m_random;
    // parametri dell'apparato

    // cas = valore assunto dalla simulazione (casuale)
    // input = valore assunto perchè ce l'ho messo io per ottere A e B iniziali

    double t, t_cas;
    double L, L_cas;
    double theta, theta_cas;
    double g, g_cas;
    double errore_L, errore_t, errore_theta;
};

PianoInclinato::PianoInclinato(unsigned int seed) : m_random(seed),
                                                    L(3),            // 3 metri
                                                    theta(0.349066), // GRADI
                                                    g(9.80505)
{
    // Tempi attesi
    t = sqrt(2.0 * L / (g * sin(theta)));
}

void PianoInclinato::esegui()
{
    // faccio le misure
    t_cas = m_random.GaussBOXMULLER(t, errore_t);
    L_cas = m_random.GaussBOXMULLER(L, errore_L);
    theta_cas = m_random.GaussBOXMULLER(theta, errore_theta);
}

void PianoInclinato::analizza()
{
    // calcolo di C
    g_cas = (2.0 * L_cas) / (t_cas * t_cas * sin(theta_cas));
}

class PianoInclinatoAttrito
{
public:
    PianoInclinatoAttrito(unsigned int seed);
    ~PianoInclinatoAttrito() {};
    void esegui();
    void analizza();
    double get_g() { return g_cas; }
    double get_mu() { return mu_cas; }

    void setErroreL(double errore) { errore_L = errore; }
    void setErroreTheta(double errore) { errore_theta = errore; }
    void setErroreT(double errore) { errore_t = errore; }

protected:
    RandomGen m_random;
    // parametri dell'apparato

    // cas = valore assunto dalla simulazione (casuale)
    // input = valore assunto perchè ce l'ho messo io per ottere A e B iniziali

    double t1, t1_cas;
    double t2, t2_cas;
    double L, L_cas;
    double theta1, theta1_cas;
    double theta2, theta2_cas;
    double mu, mu_cas;
    double g, g_cas;
    double errore_L, errore_t, errore_theta;
};

PianoInclinatoAttrito::PianoInclinatoAttrito(unsigned int seed) : m_random(seed),
                                                                  L(3),             // 3 metri
                                                                  theta1(0.174533), // RADIANTI
                                                                  theta2(0.523599),
                                                                  mu(0.05),
                                                                  g(9.80505)
{
    // Tempi attesi
    t1 = sqrt(2.0 * L / (g * (sin(theta1) - mu * cos(theta1))));
    t2 = sqrt(2.0 * L / (g * (sin(theta2) - mu * cos(theta2))));
}

void PianoInclinatoAttrito::esegui()
{
    // faccio le misure
    t1_cas = m_random.GaussBOXMULLER(t1, errore_t);
    t2_cas = m_random.GaussBOXMULLER(t2, errore_t);
    L_cas = m_random.GaussBOXMULLER(L, errore_L);
    theta2_cas = m_random.GaussBOXMULLER(theta2, errore_theta);
    theta1_cas = m_random.GaussBOXMULLER(theta1, errore_theta);
}

void PianoInclinatoAttrito::analizza()
{
    // calcolo mu
    mu_cas = ((t1_cas*t1_cas)*sin(theta1_cas) - (t2_cas*t2_cas*sin(theta2_cas)))/(t1_cas*t1_cas*cos(theta1_cas) - t2_cas*t2_cas*cos(theta2_cas));

    g_cas = (2.0 * L / (t1_cas*t1_cas * (sin(theta1_cas) - mu * cos(theta1_cas))));

}
