//
// Created by tonix on 17/11/2020.
//

#include "DicClauValor.h"


template <typename Clau, typename Valor, typename HashFunct>
DicClauValor<Clau, Valor, HashFunct>::DicClauValor() : _quants(0) {
    _M = 51;
    _taula = new node_hash*[_M];
    for (int i=0; i < _M; ++i) {
        _taula[i] = NULL;
    }
}

template <typename Clau, typename Valor, typename HashFunct>
DicClauValor<Clau,Valor,HashFunct>::node_hash::node_hash(const Clau &k, const Valor &v, node_hash* seg): _k(k), _v(v), _seg(seg) {
}

template <typename Clau, typename Valor, typename HasFunct>
void DicClauValor<Clau, Valor, HasFunct>::consulta (const Clau &k, bool &hi_es, Valor &v) const throw() {
    int i = hash(k);
    node_hash* p = _taula[i];
    hi_es = false;
    while (p != NULL and not hi_es) {
        if (p->_k == k) {
            hi_es = true;
            v = p->_v;
        }
        else {
            p = p->_seg;
        }
    }
}

template <typename Clau, typename Valor, typename HasFunct>
void DicClauValor<Clau, Valor, HasFunct>::insereix (const Clau &k, const Valor &v) throw() {
    int i = hash(k);
    node_hash *p = _taula[i];
    bool trobat = false;
    while (p != NULL and not trobat) {
        if (p->_k == k) {
            trobat = true;
        }
        else {
            p = p->_seg;
        }
    }
    if (trobat) {
        p->_v = v;
    }
    else {
        _taula[i] = new node_hash(k, v, _taula[i]);
        ++_quants;
    }
}

template <typename Clau, typename Valor, typename HasFunct>
void DicClauValor<Clau, Valor, HasFunct>::elimina (const Clau &k) throw() {
    nat i = hash(k);
    node_hash *p = _taula[i], *ant=NULL;
    bool trobat = false;
    while (p != NULL and not trobat) {
        if (p->_k == k) {
            trobat = true;
        }
        else {
            ant = p;
            p = p->_seg;
        }
    }
    if (trobat) {
        if (ant == NULL) { _taula[i] = p->seg; }
        else { ant->seg = p->seg; }
        delete(p);
        --_quants;
    }
}

//
//
//template<typename Clau, typename Valor>
//void DicClauValor<Clau, Valor>::insereix(const Clau &k, const Valor &v) throw() {
//    _arrel = insereix_bst(_arrel, k, v);
//}
//
//template<typename Clau, typename Valor>
//typename DicClauValor<Clau, Valor>::node *
//DicClauValor<Clau, Valor>::insereix_bst(node *p, const Clau &k, const Valor &v) throw() {
//    node *pare = NULL;
//    node *p_orig = p;
//    if (p == NULL) {p_orig = new node(k, v);
//    } else {
//        while (p != NULL and p->_k != k) {
//            pare = p;
//            if (k < p->_k) {p = p->_esq;}
//            else {p = p->_dret;}
//        }
//        if (p == NULL) {
//            if (k < pare->_k) {pare->_esq = new node(k, v);}
//            else {pare->_dret = new node(k, v);}
//        } else {p->_v = v;}
//    }
//    return p_orig;
//}
//
//template <typename Clau, typename Valor>
//void DicClauValor<Clau, Valor>::elimina (const Clau &k) throw() {
//    _arrel = elimina_bst(_arrel, k);
//}
//
//template <typename Clau, typename Valor>
//typename DicClauValor<Clau, Valor>::node* DicClauValor<Clau, Valor>::elimina_bst (node *n, const Clau &k) throw() {
//    node *p = n;
//    if (n != NULL) {
//        if (k < n->_k) {n->_esq = elimina_bst(n->_esq, k);}
//        else if (k > n->_k) {n->_dret = elimina_bst(n->_dret, k);}
//        else {
//            n = ajunta(n->_esq, n->_dret);
//            delete(p);
//        }
//    }
//    return n;
//}
//
//template <typename Clau, typename Valor>
//typename DicClauValor<Clau, Valor>::node* DicClauValor<Clau, Valor>::elimina_maxim (node* p) throw() {
//    node *p_orig = p, *pare = NULL;
//    while (p->_dret != NULL) {
//        pare = p;
//        p = p->_dret;
//    }
//    if (pare != NULL) {
//        pare->_dret = p->_esq;
//        p->_esq = p_orig;
//    }
//    return p;
//}
//
//template <typename Clau, typename Valor>
//typename DicClauValor<Clau, Valor>::node* DicClauValor<Clau, Valor>::ajunta (node *t1, node *t2) throw() {
//    if (t1 == NULL) {return t2;}
//    if (t2 == NULL) {return t1;}
//    node* p = elimina_maxim(t1);
//    p->_dret = t2;
//    return p;
//}
//
//template<typename Clau, typename Valor>
//DicClauValor<Clau, Valor>::node::node(const Clau &k, const Valor &v, node *esq, node *dret) : _k(k), _v(v), _esq(esq),  _dret(dret) {}
//
//template<typename Clau, typename Valor>
//void DicClauValor<Clau, Valor>::consulta(const Clau &k, bool &hi_es, Valor &v) const throw() {
//    node *n = consulta_bst(_arrel, k);
//    if (n == NULL) {
//        hi_es = false;
//    } else {
//        hi_es = true;
//        v = n->_v;
//    }
//}
//
//template<typename Clau, typename Valor>
//typename DicClauValor<Clau, Valor>::node *DicClauValor<Clau, Valor>::consulta_bst(node *n, const Clau &k) throw() {
//    while (n != NULL and k != n->_k) {
//        if (k < n->_k) { n = n->_esq; }
//        else { n = n->_dret; }
//    }
//    return n;
//}
//
//
//template <typename Clau, typename Valor>
//void DicClauValor<Clau, Valor>::llista_interval(const Clau &k1, const Clau &k2, list<Valor> &L) const throw() {
//    rllista_interval(_arrel, k1, k2, L);
//}
//
//template <typename Clau, typename Valor>
//void DicClauValor<Clau, Valor>::rllista_interval(node *n, const Clau &k1, const Clau &k2, list<Valor> &L) throw() {
//    if (n != NULL) {
//        if (k1 <= n->_k) {
//            rllista_interval(n->_esq, k1, k2, L);
//        }
//        if (k1 <= n->_k and n->_k <= k2) {
//            L.push_back(n->_v);
//        }
//        if (n->_k <= k2) {
//            rllista_interval(n->_dret, k1, k2, L);
//        }
//    }
//}
