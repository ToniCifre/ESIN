//
// Created by tonix on 17/11/2020.
//

#include "DicClau.h"


//
// Created by tonix on 17/11/2020.
//

#include "DicClauValor.h"


template<typename Clau>
void DicClau<Clau>::insereix(const Clau &k) throw() {
    _arrel = insereix_bst(_arrel, k);
}

template<typename Clau>
typename DicClau<Clau>::node *
DicClau<Clau>::insereix_bst(node *p, const Clau &k) throw() {
    node *pare = NULL;
    node *p_orig = p;
    if (p == NULL) {p_orig = new node(k);
    } else {
        while (p != NULL and p->_k != k) {
            pare = p;
            if (k < p->_k) {p = p->_esq;}
            else {p = p->_dret;}
        }
        if (p == NULL) {
            if (k < pare->_k) {pare->_esq = new node(k);}
            else {pare->_dret = new node(k);}
        }
    }
    return p_orig;
}

template <typename Clau>
void DicClau<Clau>::elimina (const Clau &k) throw() {
    _arrel = elimina_bst(_arrel, k);
}

template <typename Clau>
typename DicClau<Clau>::node* DicClau<Clau>::elimina_bst (node *n, const Clau &k) throw() {
    node *p = n;
    if (n != NULL) {
        if (k < n->_k) {n->_esq = elimina_bst(n->_esq, k);}
        else if (k > n->_k) {n->_dret = elimina_bst(n->_dret, k);}
        else {
            n = ajunta(n->_esq, n->_dret);
            delete(p);
        }
    }
    return n;
}

template <typename Clau>
typename DicClau<Clau>::node* DicClau<Clau>::elimina_maxim (node* p) throw() {
    node *p_orig = p, *pare = NULL;
    while (p->_dret != NULL) {
        pare = p;
        p = p->_dret;
    }
    if (pare != NULL) {
        pare->_dret = p->_esq;
        p->_esq = p_orig;
    }
    return p;
}

template <typename Clau>
typename DicClau<Clau>::node* DicClau<Clau>::ajunta (node *t1, node *t2) throw() {
    if (t1 == NULL) {return t2;}
    if (t2 == NULL) {return t1;}
    node* p = elimina_maxim(t1);
    p->_dret = t2;
    return p;
}

template<typename Clau>
DicClau<Clau>::node::node(const Clau &k, node *esq, node *dret) : _k(k), _esq(esq),  _dret(dret) {}

template<typename Clau>
bool DicClau<Clau>::consulta(const Clau &k) const throw() {
    node *n = consulta_bst(_arrel, k);
    if (n == NULL) return false;
    else return true;
}

template<typename Clau>
typename DicClau<Clau>::node *DicClau<Clau>::consulta_bst(node *n, const Clau &k) throw() {
    while (n != NULL and k != n->_k) {
        if (k < n->_k) n = n->_esq;
        else n = n->_dret;
    }
    return n;
}


template <typename Clau>
void DicClau<Clau>::llista_interval(const Clau &k1, const Clau &k2, list<Clau> &L) const throw() {
    rllista_interval(_arrel, k1, k2, L);
}

template <typename Clau>
void DicClau<Clau>::rllista_interval(node *n, const Clau &k1, const Clau &k2, list<Clau> &L) throw() {
    if (n != NULL) {
        if (k1 <= n->_k) {
            rllista_interval(n->_esq, k1, k2, L);
        }
        if (k1 <= n->_k and n->_k <= k2) {
            L.push_back(n->_k);
        }
        if (n->_k <= k2) {
            rllista_interval(n->_dret, k1, k2, L);
        }
    }
}
