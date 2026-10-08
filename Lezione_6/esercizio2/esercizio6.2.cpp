#include <iostream>
#include <fstream>
#include <string>
#include "funzionebase.h"
#include "fmtlib.h"
#include <cassert>
#include "solutore.h"
#include <cassert>

using namespace std;
using namespace fmt;


bool are_close(double calculated, double expected, double epsilon = 1e-9)
{
    return fabs(calculated - expected) < epsilon;
}

void test_zeroes() {
  bisezione s{};
  parabola f{3, 5, -2}; // Zeroes for this function are known: x₁ = −2, x₂ = 1/3
  s.setPrecisione(1e-8);

  assert(are_close(s.CercaZeriReference(-3.0, -1.0, f, 10000, 1e-8), -2.0)); // Zero is within (a, b)
  assert(are_close(s.CercaZeriReference(-2.0, 0.0, f, 10000, 1e-8), -2.0));  // Zero is at a
  assert(are_close(s.CercaZeriReference(-4.0, -2.0, f, 10000, 1e-8), -2.0)); // Zero is at b

  cerr << "Root finding works correctly! 🥳\n";
}



int main(int argc, char *argv[])
{
  test_zeroes();
  if (argc != 6)
  {
    cerr << "Errore con il programma, inserire: <a>, <b>, <c>  \n Inserire anche <numero di cicli> e <precisione>" << endl;
    exit(1);
  }

  double a{stod(argv[1])};
  double b{stod(argv[2])};
  double c{stod(argv[3])};
  int ncicli{stoi(argv[4])};
  double prec{stod(argv[5])};

  parabola p{a, b, c};

  cout << "il vertice è uguale a " << p.GetVertex() << endl;

  bisezione bysect{};
  double zero = bysect.CercaZeriReference(-3.0, 0.0, p, ncicli, prec);
  if (bysect.getFound() == false)
  {
    fmt::println("Troppi cicli! in più rispetto a {}!", bysect.getNMAXiterazioni());
  }
  fmt::println("x  = {}, nell' intervallo [{}; {}], con una precisione di {}, e {} cicli", zero, -3.0, 0.0, bysect.getPrec(), bysect.getNITERAZIONI());
  double zero1 = bysect.CercaZeriReference(0.0, 1.0, p, ncicli, prec);
  if (bysect.getFound() == false)
  {
    fmt::println("Troppi cicli! in più rispetto a {}!", bysect.getNMAXiterazioni());
  }
  fmt::println("x  = {}, nell' intervallo [{}; {}], con una precisione di {}, e {} cicli", zero1, 0.0, 1.0, bysect.getPrec(), bysect.getNITERAZIONI());

  return 0;
}
