//
// Created by tonix on 17/11/2020.
//

#ifndef ESIN_DICCLAUVALOR_H
#define ESIN_DICCLAUVALOR_H

#include <iostream>
#include <list>

typedef unsigned int nat;
using namespace std;

template <typename T>
class Hash {
public:
    int operator()(const T &x) const throw();
};
template <>
class Hash<string> {
public:
    int operator()(const string &x) const throw() {
        nat n = 0;
        for (nat i=0; i < x.length(); ++i) {
            n = n + x[i]*i;
        }
        return n;
    }
};

template <>
class Hash<int> {
    static long const MULT = 31415926;
public:
    int operator()(const int &x) const throw() {
        long y = ((x * x * MULT) << 20) >> 4;
        return y;
    }
};


template <typename Clau, typename Valor, typename HashFunct = Hash<Clau>>
class DicClauValor {

public:
    // Constructora per defecte. Crea un diccionari buit.
    DicClauValor();

    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
    DicClauValor(const DicClauValor &d);
    ~DicClauValor();
    DicClauValor& operator=(const DicClauValor &d);

    void consulta(const Clau &k, bool &hi_es, Valor &v) const throw();
    void insereix(const Clau &k, const Valor &v) throw();
    void elimina(const Clau &k) throw();

//    // Retorna quants elements (claus) té el diccionari.
//    nat quants() const;
//
//    // Impressió per cout de claus del diccionari en ordre ascendent, separades per
//    // un espai, començant per ’[’ i acabant per ’]’, en dues versions:
//    // Imprimeix totes les claus
//    void print() const;
//    // Imprimeix les claus entre k1 i k2 ambdós incloses. Pre: k1 <= k2
//    void print_interval(const Clau &k1, const Clau &k2) const;
//
//    // Retorna la clau més petita i la més gran respectivament.
//    // Pre: El diccionari no està buit
//    Clau min() const;
//    Clau max() const;
//
//    // Retorna la clau de la posició i-èssima (comptant-les en ordre ascendent).
//    // Pre: El diccionari no està buit. 1 <= i <= quants()
//    Clau iessim(nat i) const;


private:

    struct node_hash {
        Clau _k;
        Valor _v;
        node_hash* _seg;
        node_hash(const Clau &k, const Valor &v, node_hash* seg = NULL);
    };
    node_hash **_taula;
    nat _M;
    nat _quants;

    int hash(const Clau &k) throw() {
        HashFunct h;
        return h(k) % _M;
    }

//    static node_hash* consulta_bst(node_hash *n, const Clau &k) throw();
//    static node_hash* insereix_bst(node_hash *n, const Clau &k, const Valor &v) throw();
//    static node_hash* elimina_bst(node_hash *n, const Clau &k) throw();
//    static node_hash* elimina_maxim(node_hash *n) throw();
//    static node_hash* ajunta(node_hash *t1, node_hash* t2) throw();

};


#endif //ESIN_DICCLAUVALOR_H
