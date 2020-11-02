//
// Created by tonix on 02/11/2020.
//
// Creació d'una llista amb fantasma a partir d'un vector
//

#include <vector>
#include <cstddef>
using namespace std;
typedef unsigned int nat;

class Llista {
    // Llista simplement encadenada, amb fantasma i no circular.
private:
    struct node {
        int info;  // Informació del node
        node *seg; // Punter al següent element
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
};

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
}
