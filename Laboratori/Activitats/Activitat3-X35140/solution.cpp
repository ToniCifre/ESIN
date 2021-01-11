//
// Created by tonix on 17/12/2020.
//

#include <sstream>
using namespace std;


#include <iostream>
using namespace std;
typedef unsigned int nat;

template <typename Clau>
class dicc {

public:
    // Constructora per defecte. Crea un diccionari buit.
    dicc();

    // Destructora
    ~dicc();

    // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const Clau &k);

    // Retorna quants elements (claus) té el diccionari.
    nat quants() const;

    // Retorna la penúltima clau.
    // Pre: El diccionari té com a mínim 2 claus.
    Clau penultima() const;

private:
    struct node {
        Clau _k;      // Clau
        node* _esq;   // fill esquerre
        node* _dret;  // fill dret
        nat _n;       // Nombre de nodes del subarbre
        node(const Clau &k, node* esq = NULL, node* dret = NULL);
    };
    node *_arrel;

    static void esborra_nodes(node* m);
    static node* insereix_bst(node *n, const Clau &k, bool &ins);

    static Clau r_penultima(node* n, int i);
};


template<typename Clau>
Clau dicc<Clau>::r_penultima(node* n, int i) {
    if(i > 0){
        if(n->_esq != NULL and i <= n->_esq->_n) {
            return r_penultima(n->_esq, i - 1);
        }else if(n->_dret != NULL){
            i = i - n->_esq->_n;
            return r_penultima(n->_dret, i-1);
        }
    }
    return n->_k;
}

template<typename Clau>
Clau dicc<Clau>::penultima() const {
    return r_penultima(_arrel, quants()-1);
}

