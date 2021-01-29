//
// Created by tonix on 19/10/2020.
//

#ifndef ESIN_LLISTAITERATOR_H
#define ESIN_LLISTAITERATOR_H

#include <iostream>

using namespace std;
typedef unsigned int nat;


template <typename T>
class LlistaIterator {
private:
    struct node {
        T info;
        node* next;
        node* prev;
    };
    node* _head; // punter al fantasma
    nat _sz; // mida de la llista

    node* copiar_llista(node* orig, node* orighead,node* h) throw();
    void destruir_llista(node* p, node* h) throw();
    void swap(LlistaIterator<T>& ) throw();

public:
    LlistaIterator();
    LlistaIterator(const LlistaIterator<T>& l) throw();
    LlistaIterator<T>& operator=(const LlistaIterator<T>& l) throw();
    ~LlistaIterator() throw();

    friend class iterador;
    class iterador {
    public:
        friend class LlistaDobleEncadenada;

        const T& operator*() const throw();

        iterador& operator++() throw();
        iterador operator++(int) throw();
        iterador& operator--() throw();
        iterador operator--(int) throw();
        bool operator==(iterador it) const throw();
        bool operator!=(iterador it) const throw();

        static const int IteradorIndef = 330;
    private:
        iterador();
        node* _p; // punter al node actual
        node* _h; // punter al fantasma de la llista per
        // poder saber quan ho hem recorregut tot.
    };

    void inserir_darrera(const T& x, iterador it) throw();
    void inserir_davant(const T& x, iterador it) throw();

    void esborrar_avnc(iterador& it) throw();
    void esborrar_darr(iterador& it) throw();

    nat longitud() const throw();
    bool es_buida() const throw();

    iterador primer() const throw();
    iterador ultim() const throw();
    iterador indef() const throw();

    void mostra() const;
};


#endif //ESIN_LLISTAITERATOR_H
