//
// Created by tonix on 19/10/2020.
//

#include "Llista.h"

// Cost: (1)
template <typename T>
Llista<T>::Llista() throw() {
    _head = new node;
    _head -> next = NULL;
    _antpi = _head;
    _sz = 0;
}

// Cost: (n)
template <typename T>
typename Llista<T>::node* Llista<T>::copia_llista(node* orig) throw() {
    node* dst = NULL;
    if (orig != NULL) {
        dst = new node;
        try {
            dst -> info = orig -> info;
            dst -> next = copia_llista(orig -> next);
        } catch (...) {
            delete dst;
            throw;
        }
    }
    return dst;
}

// Cost: (n)
template <typename T>
Llista<T>::Llista(const Llista<T>& l) throw() {
    _head = copia_llista(l._head);
    _sz = l._sz;
    _antpi = _head;
    node* p = l._head;
    while (p != l._antpi) {
        _antpi = _antpi->next;
        p = p->next;
    }
}
// Cost: (1)
template <typename T>
void Llista<T>::swap(Llista<T>& L) throw() {
    node* auxn = _head;
    _head = L._head;
    L._head = auxn;
    auxn = _antpi;
    _antpi = L._antpi;
    L._antpi = auxn;
    int auxs = _sz;
    _sz = L._sz;
    L._sz = auxs;
}

// Cost: (n)
template <typename T>
Llista<T>& Llista<T>::operator=(const Llista<T>& l) throw() {
    if (this != &l) {
        Llista<T> aux = l;
        swap(aux);
    }
    return *this;
}

// Cost: (n)
template <typename T>
void Llista<T>::destrueix_llista(node* p) throw() {
    if (p != NULL) {
        destrueix_llista(p->next);
        delete p;
    }
}
// Cost: (n)
template <typename T>
Llista<T>::~Llista() throw() {
    destrueix_llista(_head);
}
// Cost: (1)
template <typename T>
void Llista<T>::insereix(const T& x) throw() {
    node* nn = new node;
    try {
        nn->info = x;
    } catch(...) { // com que el tipus T és
        delete nn; // desconegut no sabem si
        throw; // utilitza memòria dinàmica
    }

    if(_head->next == NULL){
        nn->next = _head->next;
        _head->next = nn;
        _antpi = nn;
    }else {
        nn->next = _antpi->next;
        _antpi->next = nn;
        _antpi = nn;
    }
    ++_sz;
}

// Cost: (1)
template <typename T>
void Llista<T>::esborra() throw() {
    if (_antpi->next != NULL) {
        node* todel = _antpi->next;
        _antpi->next = todel->next;
        delete todel;
        --_sz;
    }
}

// Cost: (1)
template <typename T>
nat Llista<T>::longitud() const throw() {
    return _sz;
}

// Cost: (1)
template <typename T>
bool Llista<T>::es_buida() const throw() {
    return _head->next == NULL;
    // equival a: return sz == 0
}

// Cost: (1)
template <typename T>
void Llista<T>::principi() throw() {
    _antpi = _head;
}

// Cost: (1)
template <typename T>
void Llista<T>::avanca() throw() {
    if (_antpi->next != NULL) {
        _antpi = _antpi->next;
    }
}

// Cost: (1)
template <typename T>
const T& Llista<T>::actual() const throw() {
    if (_antpi->next == NULL) {
        throw(PIIndef);
    }
    return _antpi->next->info;
}

// Cost: (1)
template <typename T>
bool Llista<T>::final() const throw() {
    return _antpi->next == NULL;
}

template <typename T>
void Llista<T>::mostra() const {
    node *aux = _head->next;
    while (aux != NULL){
        cout<<aux->info<< " ";
        aux = aux->next;
    }
    cout << endl;

}