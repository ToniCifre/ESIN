//
// Created by tonix on 19/10/2020.
//

#include "LlistaDobleEncadenada.cpp"
#include <vector>
#include <cstddef>
#include <sstream>
#include <iostream>

using namespace std;

int main() {
    string linea;
    while(getline(cin, linea)){
        vector<int> v;

        LlistaDobleEncadenada<int> l;
        LlistaDobleEncadenada<int>::iterador iterador = l.primer();

        istringstream ss(linea);
        int x;
        while(ss>>x){
            v.push_back(x);
            l.inserir_darrera(x, iterador);
            iterador++;
        }
        l.mostra();


    }

    return 0;
}
