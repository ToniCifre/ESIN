//
// Created by tonix on 17/12/2020.
//

#include <iostream>
#include <sstream>
#include "DicClau.cpp"

using namespace std;

int main() {
    string linea;
    int n;
    DicClau<int> d;
    while (getline(cin, linea)) {
        istringstream ss1(linea);
        while (ss1 >> n){
            d.insereix(n);
        }
    }
    d.print();
    cout << endl;
}
