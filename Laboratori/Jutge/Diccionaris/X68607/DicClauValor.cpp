//
// Created by tonix on 17/11/2020.
//

#include <iostream>
#include <list>

typedef unsigned int nat;
using namespace std;

//template <typename T>
//class Hash {
//public:
//    int operator()(const T &x) const throw();
//};

template <typename T>
class Hash {
    static long const MULT = 31415926;
public:
    int operator()(const int &x) const throw() {
        long y = ((x * x * MULT) << 20) >> 4;
        return y;
    }
};


template <typename Clau, typename Valor, typename HashFunct = Hash<int>>
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
    nat quants() const;
//
//    // Impressió per cout de claus del diccionari en ordre ascendent, separades per
//    // un espai, començant per ’[’ i acabant per ’]’, en dues versions:
//    // Imprimeix totes les claus
    void print() const;
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

    int hash(const Clau &k);

//    static node_hash* consulta_bst(node_hash *n, const Clau &k) throw();
//    static node_hash* insereix_bst(node_hash *n, const Clau &k, const Valor &v) throw();
//    static node_hash* elimina_bst(node_hash *n, const Clau &k) throw();
//    static node_hash* elimina_maxim(node_hash *n) throw();
//    static node_hash* ajunta(node_hash *t1, node_hash* t2) throw();
//    void print_iter(node_hash **n);

};

template <typename Clau, typename Valor, typename HashFunct>
int DicClauValor<Clau, Valor, HashFunct>::hash(const Clau &k){
    Hash<int> h;
    return h(k) % _M;
}

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
//    int i = hash(k);
    Hash<int> h;
    int i = h(k) % _M;
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


template <typename Clau, typename Valor, typename HasFunct>
void DicClauValor<Clau, Valor, HasFunct>::print() const {
    for (int i = 0; i < _M; ++i) {
        node_hash* n = _taula[i];
        if(n != NULL){
            cout<< n->_k << ' ';
        }
    }
}

//template <typename Clau, typename Valor, typename HasFunct>
//void DicClauValor<Clau, Valor, HasFunct>::print_iter(DicClauValor::node_hash **n) {
//
//
//}

template<typename Clau, typename Valor, typename HashFunct>
DicClauValor<Clau, Valor, HashFunct>::~DicClauValor() {

}

template<typename Clau, typename Valor, typename HashFunct>
nat DicClauValor<Clau, Valor, HashFunct>::quants() const {
    return _quants;
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
