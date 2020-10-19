//
// Created by tonix on 13/10/2020.
//
// Exercici 4.2
//

#ifndef _LLISTA_HPP
#define _LLISTA_HPP
#include <vector>
#include <cstddef>
#include <sstream>
#include <iostream>

using namespace std;
typedef unsigned int nat;

class Llista {
    // Llista doblement encadenada, circular i amb fantasma.
private:
    struct node {
        int info;  // Informació del node
        node *seg; // Punter al següent element
    };

    nat _long;   // Nombre d’elements


public:
    typedef node* llista ;
    node *_prim; // Punter a l’element fantasma
    Llista();
    // Pre: True
    // Post: El p.i. és una llista buida.

    Llista(const vector<int> &v);
    // Pre: True
    // Post: El p.i. conté els elements de v amb el mateix ordre.

    ~Llista();
    // Post: Destrueix els elements del p.i.

    nat longitud() const;
    // Pre: True
    // Post: Retorna el nombre d’elements del p.i.

    void mostra() const;
    // Pre: True
    // Post: Mostra el p.i. pel canal estàndard de sortida.

    void split(llista& L, int x, llista& la, llista& lb);
    // Pre: True
    // Post: Mostra el p.i. en ordre invers pel canal estàndard de sortida.
};
#endif

Llista::Llista() {
    _prim = new node;
    _prim -> seg = NULL;
    _long = 0;
}

Llista::Llista(const vector<int> &v) {
    _prim = new node;
    _prim -> seg = NULL;
    _long = 0;

    node *aux = _prim;

    for (auto i = v.begin(); i != v.end(); ++i){
        aux ->seg = new node;
        aux = aux ->seg;
        aux ->info = *i;
        aux ->seg = NULL;

        _long++;
    }
    _prim = _prim ->seg;
}

Llista::~Llista() {
    delete(_prim);
}

nat Llista::longitud() const {
    return _long;
}

void Llista::mostra() const {
    node *aux = _prim;
    while (aux != NULL){
        cout<<aux->info<< " ";
        aux = aux->seg;
    }
    cout << endl;

}

void Llista::split(Llista::llista &L, int x, Llista::llista &la, Llista::llista &lb) {
    node *ant = NULL, *act = L;
    while (act != NULL and act->info < x){
        if (ant == NULL){
            la = act;
        }
        ant = act;
        act = act ->seg;
    }
    if (ant != NULL){
        ant->seg = NULL;
    }
    while (act != NULL and act->info == x){
        ant = act;
        act = act->seg;
        delete ant;
    }
    lb = act;
}

int main() {
    string linea;
    while(getline(cin, linea)){
        vector<int> v;

        istringstream ss(linea);
        int x;
        while(ss>>x){
            v.push_back(x);
        }

        Llista l(v);
        l.mostra();

        Llista la;
        Llista lb;
        l.split(l._prim, 5, la._prim, lb._prim);
        la.mostra();
        lb.mostra();

    }

    return 0;
}