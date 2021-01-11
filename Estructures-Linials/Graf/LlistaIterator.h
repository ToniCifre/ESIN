//
// Created by tonix on 19/10/2020.
//

#ifndef ESIN_LLISTAITERATOR_H
#define ESIN_LLISTAITERATOR_H

#include <iostream>

using namespace std;
typedef unsigned int nat;


template <typename Clau, typename Valor>
class LlistaIterator {
private:
    struct node {
        Clau _c;
        Valor _v;
        node* next;
        node* prev;
    };
    node* _head; // punter al fantasma
    nat _sz; // mida de la llista

    node* copiar_llista(node* orig, node* orighead,node* h) throw();
    void destruir_llista(node* p, node* h) throw();
    void swap(LlistaIterator<Clau,Valor>& ) throw();

public:
    LlistaIterator();
    LlistaIterator(const LlistaIterator<Clau,Valor>& l) throw();
//    LlistaIterator<Clau,Valor>& operator=(const LlistaIterator<Clau,Valor>& l) throw();
    ~LlistaIterator() throw();

    static const int MAX = 50;
    typedef pair<Clau, Valor> pair_cv;

    friend class iterador;
    class iterador {
    public:
        friend class LlistaDobleEncadenada;

        pair_cv operator*() const throw();

        iterador& operator++() throw();
        iterador operator++(int) throw();
        iterador& operator--() throw();
        iterador operator--(int) throw();
        bool operator==(iterador it) const throw();
        bool operator!=(iterador it) const throw();

        static const int IteradorIndef = 330;
        iterador();
        node* _p; // punter al node actual
        node* _h; // punter al fantasma de la llista per
    };

    void inserir(const Clau& c, const Valor& v) throw();

    void esborrar_avnc(iterador& it) throw();
    void esborrar_darr(iterador& it) throw();

    nat longitud() const throw();
    bool es_buida() const throw();

    iterador primer() const throw();
    iterador ultim() const throw();
    iterador indef() const throw();

    void mostra() const;
};



// Cost: (1)
template <typename Clau, typename Valor>
LlistaIterator<Clau,Valor>::LlistaIterator() {
    _head = new node;
    _head->next = _head->prev = _head;
    _sz = 0;
}

// Cost: (n)
template <typename Clau, typename Valor>
LlistaIterator<Clau,Valor>::LlistaIterator(const LlistaIterator<Clau,Valor> &l) throw(){
    _head = new node;
    _head->next = copiar_llista(l._head->next,
                                l._head, _head);
    _head->next->prev = _head;
    _sz = l._sz;
}

// Cost: (n)
template <typename Clau, typename Valor>
typename LlistaIterator<Clau,Valor>::node*LlistaIterator<Clau,Valor>::copiar_llista(node* orig, node* orig_head, node* h) throw() {
    node* dst = h;
    if (orig != orig_head) {
        dst = new node;
        try {
            dst->info = orig->info;
            dst->next = copiar_llista(orig->next, orig_head, h);
            dst -> next -> prev = dst;
        }
        catch (...) {
            delete dst;
            throw;
        }
    }
    return dst;
}

//// Cost: (n)
//template <typename Clau, typename Valor>
//LlistaIterator<Clau,Valor>& LlistaIterator<Clau,Valor>::operator=(const LlistaIterator<Clau,Valor> & l) throw() {
//    if (this != &l) {
//        LlistaIterator<Clau,Valor> aux = l;
//        swap(aux);
//    }
//    return *this;
//}

// Cost: (1)
template <typename Clau, typename Valor>
void LlistaIterator<Clau,Valor>::swap(LlistaIterator<Clau,Valor> &l) throw(){
    node* auxn = _head;
    _head = l._head;
    l._head = auxn;
    int auxs = _sz;
    _sz = l._sz;
    l._sz = auxs;
}

// Cost: (n)
template <typename Clau, typename Valor>
void LlistaIterator<Clau,Valor>::destruir_llista(node* p, node* h) throw(){
    if (p != h) {
        destruir_llista(p->next, h);
        delete p;
    }
}

// Cost: (n)
template <typename Clau, typename Valor>
LlistaIterator<Clau,Valor>::~LlistaIterator() throw(){
    destruir_llista(_head->next, _head);
    delete _head;
}

// Cost: (1)
template <typename Clau, typename Valor>
LlistaIterator<Clau,Valor>::iterador::iterador(){
}

// Cost: (1)
template <typename Clau, typename Valor>
pair<Clau, Valor> LlistaIterator<Clau,Valor>::iterador::operator*() const throw() {
    if (_p == _h) {
        throw (IteradorIndef);
    }
    return make_pair(_p->_c, _p->_v);
}

// Cost: (1)
template <typename Clau, typename Valor>
typename LlistaIterator<Clau, Valor>::iterador&LlistaIterator<Clau, Valor>::iterador::operator++() throw(){
    if (_p != _h) {
        _p = _p->next;
    }
    return *this;
}
// Cost: (1)
//Operador postincrement a++
template <typename Clau, typename Valor>
typename LlistaIterator<Clau, Valor>::iterador LlistaIterator<Clau, Valor>::iterador::operator++(int) throw() {
    iterador tmp(*this);
    ++(*this); // es crida al mètode de preincrement
    return tmp;
}


// Cost: (1)
template <typename Clau, typename Valor>
bool LlistaIterator<Clau, Valor>::iterador::operator==(iterador it)const throw() {
    return (_p == it._p) and (_h == it._h);
}

// Cost: (1)
template <typename Clau, typename Valor>
bool LlistaIterator<Clau, Valor>::iterador::operator!=(iterador it)const throw() {
    return not (*this == it);
}

// Cost: (1)
template <typename Clau, typename Valor>
typename LlistaIterator<Clau, Valor>::iterador&LlistaIterator<Clau, Valor>::iterador::operator--() throw() {
    if (_p != _h) {
        _p = _p->prev;
    }
    return *this;
}

// Cost: (1)

template <typename Clau, typename Valor>
typename LlistaIterator<Clau, Valor>::iterador LlistaIterator<Clau, Valor>::iterador::operator--(int) throw() {
    iterador tmp(*this);
    --(*this); // es crida al mètode de predecrement
    return tmp;
}

// Cost: (1)

template <typename Clau, typename Valor>
void LlistaIterator<Clau, Valor>::inserir(const Clau& c, const Valor& v) throw(){
    node* nn = new node;
    try {
        nn -> _c = c;
        nn -> _v = v;
    }catch(...) {
        delete nn;
        throw;
    }
    if(_sz == 0){
        _head->next = nn;
        nn->next = _head;
        nn->prev = _head;
        _head->prev = nn;
    } else{
        iterador it = ultim();
        it._p->next = nn;
        nn->prev = it._p;
        nn->next = _head;
        _head->prev = nn;
    }
    ++_sz;
}

// Cost: (1)
template <typename Clau, typename Valor>
void LlistaIterator<Clau, Valor>::esborrar_avnc(iterador& it) throw() {
    if (it._p != _head) {
        node* todel = it._p;
        todel->prev->next = todel->next;
        todel->next->prev = todel->prev;
        delete todel;
        --_sz;
        it._p = it._p -> next;
    }
}
// Cost: (1)
template <typename Clau, typename Valor>
void LlistaIterator<Clau, Valor>::esborrar_darr(iterador& it) throw() {
    if (it._p != _head) {
        node* todel = it._p;
        todel->prev->next = todel->next;
        todel->next->prev = todel->prev;
        delete todel;
        --_sz;
        it._p = it._p->prev;
    }
}
// Cost: (1)
template <typename Clau, typename Valor>
nat LlistaIterator<Clau, Valor>::longitud() const throw() {
    return _sz;
}
// Cost: (1)
template <typename Clau, typename Valor>
bool LlistaIterator<Clau, Valor>::es_buida() const throw() {
    return _sz == 0;
}
// Cost: (1)
template <typename Clau, typename Valor>
typename LlistaIterator<Clau, Valor>::iterador LlistaIterator<Clau, Valor>::primer() const throw() {
    iterador it;
    it._p = _head->next;
    it._h = _head;
    return it;
}
// Cost: (1)
template <typename Clau, typename Valor>
typename LlistaIterator<Clau, Valor>::iterador LlistaIterator<Clau, Valor>::ultim() const throw() {
    iterador it;
    it._p = _head -> prev;
    it._h = _head;
    return it;
}
// Cost: (1)
template <typename Clau, typename Valor>
typename LlistaIterator<Clau, Valor>::iterador LlistaIterator<Clau, Valor>::indef() const throw() {
    iterador it;
    it._p = _head;
    it._h = _head;
    return it;
}

template <typename Clau, typename Valor>
void LlistaIterator<Clau, Valor>::mostra() const {
    iterador i = primer();
    while (i != indef()){
        cout << (*i).first <<" ";
        i++;
    }
    cout<<endl;
}



#endif //ESIN_LLISTAITERATOR_H
