//
// Created by tonix on 22/10/2020.
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

    void inverteix();
    // Pre: True
    // Post: S’ha invertit l’ordre els elements del p.i.
    // Exemple: [2 5 3] quedaria [3 5 2]
    // No es permet usar estructures auxiliars per invertir
    // els elements ni modificar el camp info,
    // només modificar els encadenaments dels nodes.
};

#endif

Llista::Llista() {
    _prim = new node;
    _prim -> seg = NULL;
    _long = 0;
}

Llista::~Llista() {
    delete(_prim);
}

nat Llista::longitud() const {
    return _long;
}
void Llista::mostra_invertida() const {
    node *aux = _prim ->seg;
    while (aux != _prim){
        cout<<aux->info<< " ";
        aux = aux->seg;
    }
    cout << endl;

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
void Llista::inverteix() {
    node *aux = _prim;
    do{
        node *aux1 = aux->seg;
        aux->seg = aux->ant;
        aux ->ant = aux1;
        aux = aux->ant;

    }while(aux != _prim);
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
        l.mostra_invertida();

        l.inverteix();
        l.mostra_invertida();


    }

    return 0;
}