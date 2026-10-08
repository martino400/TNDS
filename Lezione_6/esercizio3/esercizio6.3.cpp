#include <iostream>
#include <fstream>
#include <string>
#include "funzionebase.h"
#include "fmtlib.h"
#include <cassert>
#include "solutore.h"

using namespace std;
using namespace fmt;

int odg(double a);

int main(int argc, char *argv[])
{
  if (argc != 7)
  {
    cout << "Errore con il programma, mancano argomenti da inserire:\n inserire <a> e <b> della funzione che ha la forma sin(b*x) - a*x*cos(b*x) \n inserire <ncicli> e <precisione> \n inserire <min> e <max> nell'intervallo!!" << endl;
    return -1;
  }

  double a{stod(argv[1])};
  double b{stod(argv[2])};
  int ncicli{stoi(argv[3])};
  double prec{stod(argv[4])};
  double min{stod(argv[5])};
  double max{stod(argv[6])};

  sincos funzione(a, b);
  bisezione bysect{};
  double zero = bysect.CercaZeriReference(min, max, funzione, ncicli, prec);
  if (bysect.getFound() == false)
  {
    fmt::println("Troppi cicli! in più rispetto a {}!", bysect.getNMAXiterazioni());
  }
  else
  {
    fmt::println("x  = {}, nell' intervallo [{}; {}], con una precisione di {}, e {} cicli", zero, min, max, bysect.getPrec(), bysect.getNITERAZIONI());
  }

  // non riesce a raggiungere una precisione migliore di 1e-15 perchè non capisco cosa c'è che non vada da chiedere al tomasi

  // for (int i = 0; i < 20; i++)
  // {
  //   if (bysect.getFound() == false)
  //   {
  //     fmt::println("Troppi cicli! in più rispetto a {}!", bysect.getNMAXiterazioni());
  //   }
  //   else
  //   {
  //     fmt::println("x  = {}, nell' intervallo [{}; {}], con una precisione di {}, e {} cicli", zero, i, i--, bysect.getPrec(), bysect.getNITERAZIONI());
  //   }
  // }

  return 0;
}

int odg(double a)
{
  int i = 0;
  for (; a > 1; i++)
  {
    a = a / 10;
  }
  return i;
}