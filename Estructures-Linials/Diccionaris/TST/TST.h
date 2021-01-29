//
// Created by tonix on 10/01/2021.
//

#ifndef ESIN_TST_H
#define ESIN_TST_H
#include "esin/error"

typedef unsigned int nat;

template <class Simbol, class Clau, class Valor>
class diccDigital {

public:
    diccDigital();
    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
    diccDigital(const diccDigital &d);
    ~diccDigital();
    diccDigital& operator=(const diccDigital &d);

    void consulta (const Clau &k, bool &hi_es, Valor &v) const throw();
    void insereix (const Clau &k, const Valor &v) throw(error);

    void elimina(const Clau &k);

private:
    struct node { // tst = ternary search tree
        Simbol _c;
        node* _esq;
        node* _dret;
        node* _cen;
        Valor _v;
    };
    node *_arrel;
    // operacions privades
    static node* rconsulta (node *n, nat i, const Clau &k) throw();
    static node* rinsereix (node *n, nat i, const Clau &k, const Valor &v) throw(error);

};


template <class Simbol, class Clau, class Valor>
diccDigital<Simbol, Clau, Valor>::diccDigital() {
    _arrel = NULL;
}

template <class Simbol, class Clau, class Valor>
diccDigital<Simbol, Clau, Valor>::~diccDigital() {
    delete _arrel;
}

template <class Simbol, class Clau, class Valor>
diccDigital<Simbol, Clau, Valor>::diccDigital(const diccDigital &d) {
    *this = d;
}

//template<class Simbol, class Clau, class Valor>
//void diccDigital<Simbol, Clau, Valor>::elimina(const Clau &k) {
//    if(n != NULL){
//        print_iter(n->_esq);
//        delete(n);
//        print_iter(n->_dret);
//    }
//}
//template <class Simbol, class Clau, class Valor>
//void diccDigital<Simbol, Clau, Valor>::elimina(node *n){

//}

template <class Simbol, class Clau, class Valor>
diccDigital<Simbol, Clau, Valor> &diccDigital<Simbol, Clau, Valor>::operator=(const diccDigital &d) {
    _arrel->_k = d._arrel->_k;
    copia(_arrel, d._arrel);
    return *this;
}


// Cost: (k.length() * log(#símbols))
template <class Simbol, class Clau, class Valor>
void diccDigital<Simbol, Clau, Valor>::consulta (const Clau &k, bool &hi_es,Valor &v) const throw() {
    node *n = rconsulta(_arrel, 0, k);
    if (n == NULL) {
        hi_es = false;
    }
    else {
        v = n->_v;
        hi_es = true;
    }
}

// Cost: (k.length() * log(#símbols))
template <class Simbol, class Clau, class Valor>
typename diccDigital<Simbol, Clau, Valor>::node*
diccDigital<Simbol, Clau, Valor>::rconsulta (node *n, nat i, const Clau &k) throw() {

}

// Cost: (k.longitud() * log(#símbols))
template <class Simbol, class Clau, class Valor>
void diccDigital<Simbol, Clau, Valor>::insereix (const Clau &k, const Valor &v) throw(error) {
    Clau k2 = k + '#'; // especial<Clau>();
    _arrel = rinsereix(_arrel, 0, k2, v);
}

template<class Simbol, class Clau, class Valor>
typename diccDigital<Simbol, Clau, Valor>::node*
diccDigital<Simbol, Clau, Valor>::rinsereix(diccDigital::node *n, nat i, const Clau &k, const Valor &v) throw(error) {
    if (n == NULL) {
        n = new node;
        n->_esq = n->_dret = n->_cen = NULL;
        n->_c = k[i];
        try {
            if (i < k.length()-1) {
                n->_cen = rinsereix(n->_cen, i+1, k, v);
            }
            else { // i == k.length()-1; k[i] == Simbol()
                n->_v = v;
            }
        }
        catch (error) {
            delete n;
            throw;
        }
    }
    else {
        if (n->_c > k[i]) {
            n->_esq = rinsereix(n->_esq, i, k, v);
        }
        else if (n->_c < k[i]) {
            n->_dret = rinsereix(n->_dret, i, k, v);
        }
        else { // (n->_c == k[i])
            n->_cen = rinsereix(n->_cen, i+1, k, v);
        }
    }
    return n;
}




#endif //ESIN_TST_H
