#include <iostream>
#include <sstream>
#include "DicClauValor.cpp"

using namespace std;

int main() {
  string linea, comanda;;
  int n, n1, n2;
  while (getline(cin, linea)) {
      DicClauValor<int, int> d;

    // Obtenim elements 1er diccionari
    istringstream ss1(linea);
    while (ss1 >> n){
      d.insereix(n,n);
    }
    cout <<"dsdsd"<< endl;
    d.print();
    cout << endl;
    bool hi_es = false;
    int v = 5;
    d.consulta(1, hi_es, v);
    cout<<v<<endl;
    cout<<hi_es<<endl;
//    cout<<d.quants()<<endl;
//    cout<<d.min()<<endl;
//    cout<<d.max()<<endl;
//    cout<<d.iessim(1)<<endl;
//    cout<<d.iessim(2)<<endl;
//    cout<<d.iessim(3)<<endl;
//    cout<<d.iessim(4)<<endl;
//    cout<<d.iessim(5)<<endl;
//    cout<<d.iessim(6)<<endl;
//    cout<<d.iessim(7)<<endl;
//    cout<<d.iessim(8)<<endl;

    // Processem comandes
//    while (getline(cin, linea) and linea != "----------") {
//      cout << linea << ": ";
//      istringstream ss2(linea);
//      ss2 >> comanda;
//
//      if (comanda == "insereix") {
//        ss2 >> n;
//        d.insereix(n);
//        cout << d.quants();
//
//      } else if (comanda == "elimina") {
//        ss2 >> n;
//        d.elimina(n);
//        cout << d.quants();
//
//      } else if (comanda == "consulta") {
//        ss2 >> n;
//        cout << d.consulta(n);
//
//      } else if (comanda == "quants") {
//        cout << d.quants();
//
//      } else if (comanda == "print") {
//        d.print();
//
//      } else if (comanda == "print_interval") {
//        ss2 >> n1 >> n2;
//        d.print_interval(n1, n2);
//
//      } else if (comanda == "min") {
//        cout << d.min();
//
//      } else if (comanda == "max") {
//        cout << d.max();
//
//      } else if (comanda == "iessim") {
//        ss2 >> n;
//        cout << d.iessim(n);
//      }
//      cout<<endl;
//    }
    if (linea == "----------")
      cout << linea << endl;
  }
}
