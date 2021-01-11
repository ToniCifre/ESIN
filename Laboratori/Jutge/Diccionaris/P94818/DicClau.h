//
// Created by tonix on 17/11/2020.
//

#ifndef ESIN_DICCLAU_H
#define ESIN_DICCLAU_H

#include <iostream>
#include <list>

typedef unsigned int nat;
using namespace std;

template <typename Clau>
class DicClau {

public:
    // Constructora per defecte. Crea un diccionari buit.
    DicClau();
    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
    DicClau(const DicClau &d);
    ~DicClau();
    DicClau& operator=(const DicClau &d);

    void insereix(const Clau &k) throw();
    void elimina(const Clau &k) throw();
    bool consulta(const Clau &k) const throw();


    // Retorna quants elements (claus) té el diccionari.
    nat quants() const;

    // Impressió per cout de claus del diccionari en ordre ascendent, separades per
    // un espai, començant per ’[’ i acabant per ’]’, en dues versions:
    // Imprimeix totes les claus
    void print() const;
    // Imprimeix les claus entre k1 i k2 ambdós incloses. Pre: k1 <= k2
    void print_interval(const Clau &k1, const Clau &k2) const;

    // Retorna la clau més petita i la més gran respectivament.
    // Pre: El diccionari no està buit
    Clau min() const;
    Clau max() const;

    // Retorna la clau de la posició i-èssima (comptant-les en ordre ascendent).
    // Pre: El diccionari no està buit. 1 <= i <= quants()
    Clau iessim(nat i) const;

    void llista_interval(const Clau &k1, const Clau &k2, list<Clau> &L) const throw();

private:

    struct node {
        Clau _k;
        node* _esq; // fill esquerre
        node* _dret; // fill dret
        node(const Clau &k, node* esq = NULL, node* dret = NULL);
    };
    node *_arrel;

    static node* consulta_bst(node *n, const Clau &k) throw();
    static node* insereix_bst(node *n, const Clau &k) throw();
    static node* elimina_bst(node *n, const Clau &k) throw();
    static node* ajunta(node *t1, node* t2) throw();
    static node* elimina_maxim(node *n) throw();

    static void rllista_interval(node *n, const Clau &k1, const Clau &k2, list<Clau> &L) throw();

    static void print_iter(node *n);

    static void elimina(node *n);
    static void copia(node *n1, node *n2);

};


#endif //ESIN_DICCLAU_H
