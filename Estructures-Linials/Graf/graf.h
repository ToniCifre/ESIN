//
// Created by tonix on 10/01/2021.
//

#ifndef ESIN_GRAF_H
#define ESIN_GRAF_H

#include <iostream>
#include <esin/error>
#include <list>
#include "LlistaIterator.h"

using namespace std;
typedef unsigned int nat;


template <typename V, typename E>
class graf {
public:
    graf() throw(error);
//    graf(const graf &g) throw(error);
//    graf& operator=(const graf &g) throw(error);
    ~graf() throw();

    void afegeix_vertex(const V &v) throw(error);
    void afegeix_aresta(const V &u, const V &v, const E &e) throw(error);

    E valor(const V &u, const V &v) const throw(error);

    bool existeix_vertex(const V &v) const throw();
    bool existeix_aresta(const V &u, const V &v) const throw(error);

    void adjacents(const V &v, list<V> &l) const throw(error);

    void successors(const V &v, list<V> &l) const throw(error);
    void predecessors(const V &v, list<V> &l) const throw(error);

    void elimina_vertex(const V &v) throw();
    void elimina_aresta(const V &u, const V &v) throw();



    typedef pair<V, V> aresta ;
    typedef LlistaIterator<V, unsigned int > vertexs;

private:
    struct node {
        vertexs _vert;
        node* next;
        node* prev;
    };
    node* _head;
};

template<typename V, typename E>
graf<V, E>::graf() throw(error) {
    _head = new node;
    _head->next = _head->prev = _head;
}

template<typename V, typename E>
graf<V, E>::~graf() throw() {

}

template<typename V, typename E>
void graf<V, E>::afegeix_vertex(const V &v) throw(error) {
    node* nn = new node;
    LlistaIterator<V,V> *lv;
    nn->_vert = lv;
    nn->_vert.inserir(v,v);
    nn->next = _head;
    nn->prev = _head->prev;
    _head->prev->next = nn;
    _head->prev = nn;
}


#endif //ESIN_GRAF_H
