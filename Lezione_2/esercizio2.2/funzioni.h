#include <fstream>
#include <iostream>
#include <string>
// argc si becca il numero di parametri passati dalla linea di comando
// argv si becca i parametri passati dalla linea di comando
// il primo parametro è sempre il nome dell'eseguibile
using namespace std;
#include "Vettore.h"
//Leggo file
Vettore Read(int ndata, const char *filename);
//Media vettore, prendo reference in modo da non fare una copia dei dati sulla funzione e allo stesso tempo const mi permette che non vengano modificati
double media(const Vettore &v);
//Mediana vettore
double mediana(Vettore a);
//Varianza vettore
double varianza(const Vettore &a, double media);
//Selection sort
void ordina(Vettore& ordinato);
// stampa a video
void Print(const Vettore& data);
// stampa su file
void Print(const Vettore& data, const char *filename);