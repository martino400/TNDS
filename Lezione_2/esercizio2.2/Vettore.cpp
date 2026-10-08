#include "Vettore.h"
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cassert>

// costruttore senza argomenti
Vettore::Vettore()
{
    m_N = 0;
    m_v = NULL;
}

// costruttore con dimensione
Vettore::Vettore(int N)
{
    if (N < 0)
    {
        cout << "Errore!" << endl;
        exit(33);
    }
    else
    {
        m_N = N;
        m_v = new double[N];
        for (int i = 0; i < N; i++)
        {
            m_v[i] = 0;
        }
    }
}

void Vettore::crashIfInvalidIndex(int i) const
{
    // Se `i` non è un indice valido nell'array, stampa un messaggio
    // di errore e termina il programma
    if (i < 0 || i >= m_N)
    {
        cerr << "Errore, indice " << i << ", dimensione " << m_N << endl;
        exit(1);
    }
}

// distruttore
Vettore::~Vettore()
{
    delete[] m_v;
}

// copia vettore
Vettore::Vettore(const Vettore &vett)
{
    m_N = vett.GetN();
    m_v = new double[m_N];
    for (int i = 0; i < m_N; i++)
    {
        m_v[i] = vett.GetComponent(i);
    }
}

// assegnazione vettore
Vettore & Vettore::operator=(const Vettore& vett)
{
    m_N = vett.GetN();
    if(m_v) delete[] m_v;
    m_v = new double[m_N];
    for (int i = 0; i < m_N; i++)
    {
        m_v[i] = vett.GetComponent(i);
    }
    return *this;
}

void Vettore::SetComponent(int i, double a)
{
    assert(i<GetN());
    crashIfInvalidIndex(i);
    m_v[i] = a;
}

double Vettore::GetComponent(int i) const
{
    assert(i<GetN());
    crashIfInvalidIndex(i);
    return m_v[i];
}

// metodo interno

void Vettore::Swap(int primo, int successivo)
{
    assert(primo<GetN());
    assert(successivo<GetN());

    double temp = m_v[primo];
    m_v[primo] = m_v[successivo];
    m_v[successivo] = temp;
}

double &Vettore::operator[](int i) const
{
    crashIfInvalidIndex(i);
    return m_v[i];
}

// overloading del move constructor

Vettore::Vettore(Vettore &&V) {
  cout << "Calling move constructor" << endl;
  m_N = V.m_N;
  m_v = V.m_v;
  V.m_N = 0;
  V.m_v = nullptr;
  cout << "Move constructor called" << endl;
}

// overloading del move assignment operator

Vettore &Vettore::operator=(Vettore &&V) {
  cout << "Calling move assignment operator " << endl;
  delete[] m_v;

  m_N = V.m_N;
  m_v = V.m_v;

  V.m_N = 0;
  V.m_v = nullptr;
  cout << "Move assignment operator called" << endl;
  return *this;
}
