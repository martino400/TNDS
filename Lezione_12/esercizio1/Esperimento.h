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

    m_Acas = ((m_lambda2 * m_lambda2) * (m_n2cas * m_n2cas) - (m_lambda1 * m_lambda1) * (m_n1cas * m_n1cas)) / -((m_lambda1 * m_lambda1) - (m_lambda2 * m_lambda2));
    m_Bcas = ((m_n2cas * m_n2cas) - (m_n1cas * m_n1cas)) / (1 / (m_lambda2 * m_lambda2) - 1 / (m_lambda1 * m_lambda1));
}

class EsperimentoAttrito
{
public:
    EsperimentoAttrito();
    EsperimentoAttrito(unsigned int seed);
    ~EsperimentoAttrito() {};

    void analizza();
    void esegui();

    // mi serve per poterlo fare prima con un valore di R e poi un'altro
    void setRmisurato(double misura) { m_Rmisurato = misura; }
    void setSigmaDeltaX(double misura) { m_sigmapos = misura; }
    void setSigmaDeltaT(double misura) { m_sigmat = misura; }
    void setSigmaRagg(double misura) { m_sigmragg = misura; }

    double getEta() { return m_eta_casuale; }
    double getSigmaDeltaT() { return m_sigmat; }
    double getSigmaDeltaRagg() { return m_sigmragg; }

    double getSigmaDeltaX() { return m_sigmapos; }

protected:
    RandomGen m_random;
    double m_sigmat, m_sigmapos, m_sigmragg;
    double m_rho, m_rho0;
    double m_deltaspazio_casuale;
    double m_Rmisurato, m_Rcasuale;
    double m_g;
    double m_eta_misurato, m_eta_casuale;
    double m_velmisurato, m_velcasuale;
    double m_tempi_misurato, m_tempi_casuale;
    double m_deltaspazio;
};

EsperimentoAttrito::EsperimentoAttrito(unsigned int seed, double sigmat) : m_random(seed),
                                                            m_sigmat(sigmat),
                                                            m_sigmapos(0.001),
                                                            m_sigmragg(0.0001),
                                                            m_rho(2700),
                                                            m_rho0(1250),
                                                            m_g(9.81),
                                                            m_eta_misurato(0.83),
                                                            m_deltaspazio(60) {

                                                            };

void EsperimentoAttrito::esegui()
{

    // trovo velocità attese per quella eta atteso
    m_velmisurato = 2. / 9. * (m_Rmisurato * m_Rmisurato) / m_eta_misurato * (m_rho - m_rho0) * m_g;

    // trovo i tempi
    m_tempi_misurato = m_deltaspazio / m_velmisurato;

    // lancio simulazione
    m_tempi_casuale = m_random.GaussBOXMULLER(m_tempi_misurato, m_sigmat);
    m_Rcasuale = m_random.GaussBOXMULLER(m_Rmisurato, m_sigmragg);
    m_deltaspazio_casuale = m_random.GaussBOXMULLER(m_deltaspazio, m_sigmapos);
}

void EsperimentoAttrito::analizza()
{
    // calcolo velcasuale
    m_velcasuale = m_deltaspazio_casuale / m_tempi_casuale;

    // calcolo eta_casuale
    m_eta_casuale = 2. / 9. * (m_Rcasuale * m_Rcasuale) / m_velcasuale * (m_rho - m_rho0) * m_g;
}

//le due righe in cui calcolo i valori attesi, posso metterle all'interno di un nuovo metodo "Calcolo valori attesi", così posso reinvocarlo più volte
//la cosa migliore è che il costruttore invochi un metodo che le rinizializza.

