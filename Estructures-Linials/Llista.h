//
// Created by tonix on 19/10/2020.
//

#ifndef ESIN_LLISTA_H
#define ESIN_LLISTA_H

#include <iostream>

using namespace std;
typedef unsigned int nat;

template <typename T>
class Llista {
public:
    Llista() throw();
    Llista(const Llista<T>& l) throw();
    Llista<T>& operator=(const Llista<T>& l) throw();
    ~Llista() throw();

    void insereix(const T& x) throw();

    void avanca() throw();
    void esborra() throw();
    void principi() throw();
    const T& actual() const throw();

    bool final() const throw();
    bool es_buida() const throw();

    void mostra() const;

    nat longitud() const throw();

    static const int PIIndef = 320;
private:
    struct node {
        T info;
        node* next;
    };
    node* _head; // punter al fantasma
    node* _antpi; // punter al node anterior al punt d'interès
    nat _sz; // mida de la llista

    void swap(Llista<T>& l) throw();
    void destrueix_llista(node* p) throw();
    node* copia_llista(node* orig) throw();
};

#endif //ESIN_LLISTA_H
