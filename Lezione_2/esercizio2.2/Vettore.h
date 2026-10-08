#ifndef __Vettore_h__
#define __Vettore_h__

#include <iostream>
#include <fstream>

using namespace std;

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
    //perchè la uso quando passo il vettore come 
    //const Vettore& v
    int GetN() const { return m_N; };

    // Modifica la componente i-esima
    void SetComponent(int, double);

    // Accede alla componente i-esima
    double GetComponent(int) const;

    double &operator[](int i) const; // operatore che mi RESTITUISCE IL VALORE DELL'I-ESIMA CELLA

    // metodi interni
    void Swap(int, int);

    //move function
    Vettore(Vettore &&V);

    Vettore &operator=(Vettore &&V);


private:
    int m_N;                             // dimensione del vettore
    double *m_v;                         // vettore di dati
    void crashIfInvalidIndex(int) const; // verifica che un elemento sia corretto
};

#endif
