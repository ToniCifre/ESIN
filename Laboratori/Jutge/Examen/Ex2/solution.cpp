//
// Created by tonix on 17/11/2020.
//

#include <iostream>
using namespace std;
typedef unsigned int nat;

class dicc {
public:
    dicc();  // Constructora per defecte. Crea un diccionari buit.

    ~dicc(); // Destructora

    // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const string &k);

    nat quantes_comencen(string inicials) const;
    // Pre: inicials no conté el char ’#’
    // Post: Retorna el nº de claus que comencen per algun dels caràcters que conté inicials

private:
    struct node {
        char _c;    // Símbol posició i-èssima de la clau
        node* _esq; // Fill esquerra, apunta a símbols mateixa posició formant un BST
        node* _cen; // Fill central, apunta a símbols següent posició
        node* _dre; // Fill dret, apunta a símbols mateixa posició formant un BST
        node(const char &c, node* esq = NULL, node* cen = NULL, node* dre = NULL);
    };
    node* _arrel;
    static void esborra_nodes(node* t);
    static node* insereix(node *t, nat i, const string &k);

    // Aquí va l’especificació dels mètodes privats addicionals
    nat rconsulta(node *n, const char &c) const;
    void rconsulta2(node *n, nat &i) const;
};

nat dicc::quantes_comencen(string inicials) const {
    // Cost: (Ninicials * nclaus)
    nat sum = 0;
    for (nat i = 0; i< inicials.size();i++){
        sum += rconsulta(_arrel, inicials[i]);
    }
    return sum;
}

nat dicc::rconsulta(dicc::node *n, const char &c) const{
    // Cost: (Nombre ded claus inicials inserides)lineal
    if (n != NULL) {
        if (n->_c > c) {
            return rconsulta(n->_esq, c);
        }
        else if (n->_c < c) {
            return rconsulta(n->_dre, c);
        }
        else if (n->_c == c) {
            nat i = 0;
            rconsulta2(n->_cen, i);
            return i;
        }
    }
    return 0;
}

void dicc::rconsulta2(dicc::node *n, nat &i) const{
    // Cost: (nombre de nodes) lineal
    if (n != NULL) {
        if(n->_c == '#') { i = i + 1; }
        rconsulta2(n->_esq, i);
        rconsulta2(n->_dre, i);
        rconsulta2(n->_cen, i);
    }
}
