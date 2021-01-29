//
// Created by tonix on 13/10/2020.
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
        node *ant; // Punter a l’anterior element
    };
    node *_prim; // Punter a l’element fantasma
    nat _long;   // Nombre d’elements

public:
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

    void mostra_invertida() const;
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
    _prim -> ant = NULL;
    _prim -> seg = NULL;
    _long = 0;

    node *aux = _prim;

    for (auto i = v.begin(); i != v.end(); ++i){
        aux ->seg = new node;
        aux->seg->ant = aux;
        aux = aux ->seg;
        aux ->info = *i;
        aux ->seg = NULL;

        _long++;
    }
    aux->seg = _prim;
    _prim->ant = aux;
}

Llista::~Llista() {
    delete(_prim);
}

void Llista::mostra() const {
    node *aux = _prim;
    while (aux != NULL){
        cout<<aux->info<< " ";
        aux = aux->seg;
    }
    cout << endl;

}

nat Llista::longitud() const {
    return _long;
}

