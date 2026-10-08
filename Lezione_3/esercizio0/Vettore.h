#ifndef __Vettore_h__
#define __Vettore_h__
//DICHIARAZIONE 
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

template <typename T>
class Vettore
{
public:
    // costruttori
    Vettore();      // creo vettore
    Vettore(int N); // stabilisco la dimensione

    // distruttori
    ~Vettore(); // serve per deallocare la memoria

    // costruzione di tipo copia
    Vettore(const Vettore &vett);

    // operatore di assegnazione
    Vettore &operator=(const Vettore &);

    // Accede alla dimensione del vettore, serve che sia costante
    // perchè la uso quando passo il vettore come
    // const Vettore& v
    int GetN() const { return m_N; };

    // Modifica la componente i-esima
    void SetComponent(int, T);

    // Accede alla componente i-esima
    T GetComponent(int) const;

    T &operator[](int i) const; // operatore che mi RESTITUISCE IL VALORE DELL'I-ESIMA CELLA

    // metodi interni
    void Swap(int, int);

    // move function
    Vettore(Vettore &&V);

    Vettore &operator=(Vettore &&V);

private:
    int m_N;                             // dimensione del vettore
    T *m_v;                              // vettore di dati
    void crashIfInvalidIndex(int) const; // verifica che un elemento sia corretto
};





//IMPLEMENTAZIONE 
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

// costruttore senza argomenti
template <typename T> Vettore<T>::Vettore()
{
    m_N = 0;
    m_v = NULL;
}

// costruttore con dimensione
template <typename T>
Vettore<T>::Vettore(int N)
{
    assert(N > 0);
    m_N = N;
    m_v = new double[N];
    for (int i = 0; i < N; i++)
    {
        m_v[i] = 0;
    }
}

template <typename T>
void Vettore<T>::crashIfInvalidIndex(int i) const
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
template <typename T>
Vettore<T>::~Vettore()
{
    delete[] m_v;
}

// copia vettore
template <typename T>
Vettore<T>::Vettore(const Vettore &vett)
{
    m_N = vett.GetN();
    m_v = new T[m_N];
    for (int i = 0; i < m_N; i++)
    {
        m_v[i] = vett.GetComponent(i);
    }
}

// assegnazione vettore
template <typename T>
Vettore<T> &Vettore<T>::operator=(const Vettore &vett)
{
    m_N = vett.GetN();
    if (m_v)
        delete[] m_v;
    m_v = new T[m_N];
    for (int i = 0; i < m_N; i++)
    {
        m_v[i] = vett.GetComponent(i);
    }
    return *this;
}

template <typename T>
void Vettore<T>::SetComponent(int i, T a)
{
    assert(i < GetN());
    crashIfInvalidIndex(i);
    m_v[i] = a;
}

template <typename T>
T Vettore<T>::GetComponent(int i) const
{
    assert(i < GetN());
    crashIfInvalidIndex(i);
    return m_v[i];
}

// metodo interno

template <typename T>
void Vettore<T>::Swap(int primo, int successivo)
{
    assert(primo < GetN());
    assert(successivo < GetN());

    double temp = m_v[primo];
    m_v[primo] = m_v[successivo];
    m_v[successivo] = temp;
}

template <typename T> T &Vettore<T>::operator[](int i) const
{
    crashIfInvalidIndex(i);
    return m_v[i];
}

// overloading del move constructor

template <typename T>
Vettore<T>::Vettore(Vettore &&V)
{
    cout << "Calling move constructor" << endl;
    m_N = V.m_N;
    m_v = V.m_v;
    V.m_N = 0;
    V.m_v = nullptr;
    cout << "Move constructor called" << endl;
}

// overloading del move assignment operator

template <typename T>
Vettore<T> &Vettore<T>::operator=(Vettore &&V)
{
    cout << "Calling move assignment operator " << endl;
    delete[] m_v;

    m_N = V.m_N;
    m_v = V.m_v;

    V.m_N = 0;
    V.m_v = nullptr;
    cout << "Move assignment operator called" << endl;
    return *this;
}

#endif
