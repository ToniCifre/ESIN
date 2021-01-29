//
// Created by tonix on 17/11/2020.
//

#include <cstddef>
using namespace std;
typedef unsigned int nat;

template <typename T>
class deque {
public:
    deque();
    // Pre: True
    // Post: El p.i. és una deque buida.
    // Cost: (1)

    deque(const deque &dq);
    // Pre: True
    // Post: El p.i. conté una còpia de dq.
    // Cost: (n)

    ~deque();
    // Post: Destrueix els elements del p.i.
    // Cost: (n)

    nat size() const;
    // Pre: True
    // Post: Retorna el nombre d’elements de la deque.
    // Cost: (1)

    bool empty() const;
    // Pre: True
    // Post: Retorna true si la deque és buida; false en cas contrari.
    // Cost: (1)

    T front() const;
    // Pre: La deque no és buida.
    // Post: Retorna el primer element de la deque.
    // Cost: (1)

    T rear() const;
    // Pre: La deque no és buida.
    // Post: Retorna l’últim element de la deque.
    // Cost: (1)

    void push(T e);
    // Pre: True
    // Post: Insereix un element al davant de la deque.
    // Cost: (1)

    void inject(T e);
    // Pre: True
    // Post: Insereix un element al darrera de la deque.
    // Cost: (1)

    void pop();
    // Pre: La deque no és buida.
    // Post: Elimina el primer element de la deque.
    // Cost: (1)

    void eject();
    // Pre: La deque no és buida.
    // Post: Elimina l’últim element de la deque.
    // Cost: (1)

private:
    /* Double-ended queue implementada amb una llista doblement encadenada,
       sense fantasma i circular. */
    struct node {
        T info;    // Informació del node
        node *seg; // Punter al següent element
        node *ant; // Punter a l’anterior element
    };
    node *_prim; // Punter al primer element
    nat _long;   // Nombre d’elements

    // Aquí va l’especificació dels mètodes privats addicionals
};

template<typename T>
void deque<T>::push(T e) {
    // Cost: (1)
    node* nn = new node;
    try {
        nn->info = e;
    }catch(...) {
        delete nn;
        throw;
    }
    if(_long == 0){
        nn->seg = nn;
        nn->ant = nn;
        _prim = nn;
    } else{
        nn->seg = _prim;
        nn->ant = _prim->ant;
        _prim->ant = nn;
        nn->ant->seg = nn;
        _prim = nn;
    }
    _long++;
}

template<typename T>
void deque<T>::inject(T e) {
    // Cost: (1)
    node* nn = new node;
    try {
        nn->info = e;
    }catch(...) {
        delete nn;
        throw;
    }
    if(_long == 0){
        nn->seg = nn;
        nn->ant = nn;
        _prim = nn;
    } else{
        nn->ant = _prim->ant;
        nn->seg = _prim;
        _prim -> ant = nn;
        nn -> ant -> seg = nn;
    }
    _long++;
}

template<typename T>
void deque<T>::pop() {
    // Cost: (1)
    if(_long > 1){
        node *n = _prim;
        _prim = n->seg;
        _prim->ant = n->ant;
        n->ant->seg = _prim;
        delete n;
        _long--;
    } else if(_long == 1){
        node *n = _prim;
        _prim = NULL;
        delete n;
        _long--;
    }
}

template<typename T>
void deque<T>::eject() {
    // Cost: (1)
    if(_long > 1){
        node *n = _prim->ant;
        _prim->ant = n->ant;
        n->ant->seg = _prim;
        delete n;
        _long--;
    } else if(_long == 1){
        node *n = _prim;
        _prim = NULL;
        delete n;
        _long--;
    }
}