//
// Created by tonix on 17/11/2020.
//

#include <iostream>
#include <sstream>
using namespace std;
typedef unsigned int nat;

template <typename Clau>
class dicc {

public:
    // Constructora per defecte. Crea un diccionari buit.
    dicc();

    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
    dicc(const dicc &d);
    ~dicc();
    dicc& operator=(const dicc &d);

    // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const Clau &k);

    // Elimina la clau k del diccionari. Si no hi era, no fa res.
    void elimina(const Clau &k);

    // Consulta si la clau k està en el diccionari.
    bool consulta(const Clau &k) const;

    // Retorna quants elements (claus) té el diccionari.
    nat quants() const;

    nat quants_fulles() const;

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

private:
    struct node {
        Clau _k;
        node* _esq; // fill esquerre
        node* _dret; // fill dret
        node(const Clau &k, node* esq = NULL, node* dret = NULL);
    };
    node *_arrel;

    static node* consulta_bst(node *n, const Clau &k);
    static node* insereix_bst(node *n, const Clau &k);
    static node* elimina_bst(node *n, const Clau &k);
    static node* ajunta(node *t1, node* t2) ;
    static node* elimina_maxim(node *n);

    static void print_iter(node *n);
    static nat quants_iter(node *n);
    static nat quants_fulles_iter(node *n);
    static nat iessim_iret(node *n, nat *i);
};

template<typename Clau>
void dicc<Clau>::insereix(const Clau &k) {
    _arrel = insereix_bst(_arrel, k);
}

template<typename Clau>
typename dicc<Clau>::node *
dicc<Clau>::insereix_bst(node *n, const Clau &k) {
    node *pare = NULL;
    node *p_orig = n;
    if (n == NULL) {p_orig = new node(k);
    } else {
        while (n != NULL and n->_k != k) {
            pare = n;
            if (k < n->_k) {n = n->_esq;}
            else {n = n->_dret;}
        }
        if (n == NULL) {
            if (k < pare->_k) {pare->_esq = new node(k);}
            else {pare->_dret = new node(k);}
        }
    }
    return p_orig;
}

template <typename Clau>
void dicc<Clau>::elimina (const Clau &k) {
    _arrel = elimina_bst(_arrel, k);
}

template <typename Clau>
typename dicc<Clau>::node* dicc<Clau>::elimina_bst (node *n, const Clau &k) {
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
typename dicc<Clau>::node* dicc<Clau>::elimina_maxim (node* n) {
    node *p_orig = n, *pare = NULL;
    while (n->_dret != NULL) {
        pare = n;
        n = n->_dret;
    }
    if (pare != NULL) {
        pare->_dret = n->_esq;
        n->_esq = p_orig;
    }
    return n;
}

template <typename Clau>
typename dicc<Clau>::node* dicc<Clau>::ajunta (node *t1, node *t2) {
    if (t1 == NULL) {return t2;}
    if (t2 == NULL) {return t1;}
    node* p = elimina_maxim(t1);
    p->_dret = t2;
    return p;
}

template<typename Clau>
dicc<Clau>::node::node(const Clau &k, node *esq, node *dret) : _k(k), _esq(esq),  _dret(dret) {}

template<typename Clau>
bool dicc<Clau>::consulta(const Clau &k) const {
    node *n = consulta_bst(_arrel, k);
    if (n == NULL) return false;
    else return true;
}

template<typename Clau>
typename dicc<Clau>::node *dicc<Clau>::consulta_bst(node *n, const Clau &k) {
    while (n != NULL and k != n->_k) {
        if (k < n->_k) n = n->_esq;
        else n = n->_dret;
    }
    return n;
}

template<typename Clau>
dicc<Clau>::dicc() {
    _arrel = NULL;
}

template<typename Clau>
dicc<Clau>::~dicc() {

}

template<typename Clau>
void dicc<Clau>::print() const {
    cout << "[";
    print_iter(_arrel);
    cout << "]";
}

template<typename Clau>
void dicc<Clau>::print_iter(dicc::node *n) {
    if(n != NULL){
        print_iter(n->_esq);
        cout<< n->_k << ' ';
        print_iter(n->_dret);
    }
}

template<typename Clau>
nat dicc<Clau>::quants() const {
    return quants_iter(_arrel);
}

template<typename Clau>
nat dicc<Clau>::quants_iter(node *n) {
    if(n) return quants_iter(n->_esq) + quants_iter(n->_dret) + 1;
    return 0;
}


template<typename Clau>
nat dicc<Clau>::quants_fulles() const {
    return quants_fulles_iter(_arrel);
}

template<typename Clau>
nat dicc<Clau>::quants_fulles_iter(node *n) {
    if(n){
        if(!n->_dret and !n->_esq) return 1;
        else return quants_fulles_iter(n->_esq) + quants_fulles_iter(n->_dret);
    }
    return 0;
}

template<typename Clau>
Clau dicc<Clau>::min() const {
    if (_arrel){
        node *n = _arrel;
        while (n->_esq != NULL) {
            n = n->_esq;
        }
        return n->_k;
    }
    return 0;
}

template<typename Clau>
Clau dicc<Clau>::max() const {
    if (_arrel){
        node *n = _arrel;
        while (n->_dret != NULL) {
            n = n->_dret;
        }
        return n->_k;
    }
    return 0;
}

template<typename Clau>
Clau dicc<Clau>::iessim(nat i) const {
    return iessim_iret(_arrel, &i);
}

template<typename Clau>
nat dicc<Clau>::iessim_iret(node *n, nat *i) {
    int k = 0;
    if(n != NULL and *i > 0){

        k = iessim_iret(n->_esq, i);
        --*i;
        if (*i == 0) {
            k = n->_k;
        }
        if(k == 0) k = iessim_iret(n->_dret, i);


    }
    return k;
}
