#include <iostream>
#include "Vettore.h"

int main()
{
    Vettore w;
    cout << "Vettore di dimensione " << w.GetN() << endl;
    // cout << "Componenti del vettore" << w.GetComponent(1) << endl; // da errore ovviamente perchè la dimensione è di tipo NULL

    // Vettore v(-1); // restituisce errore --> uso della funzione exit(33)

    Vettore z(2);

    // restituisce 0 perchè ho costruito in modo che all'inizio l'array sia formato da soli zeri
    for (int i = 0; i < z.GetN(); i++)
    {
        cout << " " << z.GetComponent(i) << "\n";
    }

    // controllo che funzioni bene SetComponent
    z.SetComponent(0, 5);
    z.SetComponent(1, 53);

    cout << "Nella cella " << 1 << " di z = " << z.GetComponent(0) << "\n";
    cout << "Nella cella " << 2 << " di z = " << z.GetComponent(1) << "\n";

    z.Swap(0, 1); // controllo funzione Swap, funziona

    cout << "Nella cella " << 1 << " di z = " << z.GetComponent(0) << "\n";
    cout << "Nella cella " << 2 << " di z = " << z.GetComponent(1) << "\n";

    // provo a usarlo a modi puntatore

    Vettore *vp = new Vettore(10);
    for (int i = 0; i < vp->GetN(); i++)
    {
        cout << " " << vp->GetComponent(i) << "\n";
    }
    cout << "Dimensione vp = " << vp->GetN() << "\n";

 

    delete vp;

    return 0;
}