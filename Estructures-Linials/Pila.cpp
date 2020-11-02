//
// Created by tonix on 05/10/2020.
//

#include "Pila.h"

// Cost: (1)
template <typename T>
Pila<T>::Pila() throw() {
    _pl = 0;
}

// Cost: (n)
template <typename T>
void Pila<T>::copiar(const Pila<T> &p) throw() {
    for (int i=0; i < p._pl; ++i) {
        _taula[i] = p._taula[i];
    }
    _pl = p._pl;
}

// Cost: (n)
template <typename T>
Pila<T>::Pila(const Pila<T> &p) throw() {
    copiar(p);
}

// Cost: (n)
template <typename T>
Pila<T>& Pila<T>::operator=(const Pila<T> &p) throw()
{
    if (this != &p) {
        copiar(p);
    }
    return *this;
}

// Cost: (1)
template <typename T>
Pila<T>::~Pila() throw() {
    // No es fa res ja que no s'usa memòria dinàmica.
}

// Cost: (1)
template <typename T>
void Pila<T>::apilar(const T &x) throw() {
    if (es_plena()) {
        throw PilaPlena;
    }
    _taula[_pl] = x;
    ++_pl;
}

// Cost: (1)
template <typename T>
void Pila<T>::desapilar() throw() {
    if (es_buida()) {
        throw PilaBuida;
    }
    --_pl;
}

// Cost: (1)
template <typename T>
const T& Pila<T>::cim() const throw() {
    if (es_buida()) {
        throw (PilaBuida);
    }
    return _taula[_pl-1];
}

// Cost: (1)
template <typename T>
bool Pila<T>::es_buida() const throw() {
    return _pl == 0;
}

// Cost: (1)
template <typename T>
bool Pila<T>::es_plena() const throw() {
    return _pl == MAX;
}

// Cost: (n)
template <typename T>
Pila<T> Pila<T>::operator&(const T &x) const throw() {
    Pila<T> p(*this); // constructor per còpia
    p.aPilar(x);
    return p;
}

// Cost: (n)
template <typename T>
Pila<T> Pila<T>::resta() const throw() {
    Pila<T> p(*this); // constructor per còpia
    p.desaPilar();
    return p;
}

