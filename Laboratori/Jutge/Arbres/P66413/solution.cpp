//
// Created by tonix on 02/11/2020.
//
// Recorreguts recursius d'un arbre general
//

#include <iostream>
#include <stack>
#include <cstdlib>
using namespace std;
typedef unsigned int nat;

template <typename T>
class Arbre {
private:
    Arbre(): _arrel(NULL) {};
    struct node {
        T info;
        node* primf;
        node* seggerm;
    };
    node* _arrel;
    static node* copia_arbre(node* p);
    static void destrueix_arbre(node* p) throw();

public:
    // Construeix un Arbre format per un únic node que conté a x.
    Arbre(const T &x);

    // Tres grans.
    Arbre(const Arbre<T> &a);
    Arbre& operator=(const Arbre<T> &a);
    ~Arbre() throw();

    // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
    void afegir_fill(Arbre<T> &a);

    static const int ArbreInvalid = 400;

    // Escriu una línia amb el recorregut en preodre especular de l’arbre
    // Cada element ha de sortir precedit d’un espai.
    void preordre_especular();
    void toni(node* p) ;
};


template <typename T>
void Arbre<T>::preordre_especular(){
    toni(_arrel);
}

template <typename T>
void Arbre<T>::toni(node* p){
    if(p!= NULL){
        toni(p->primf);
        cout<<" "<< p->info;
        toni(p->seggerm);
    }
}

template <typename T>
typename Arbre<T>::node* Arbre<T>::copia_arbre(node* p) {
    node* aux = NULL;
    if (p != NULL) {
        aux = new node;
        try {
            aux -> info = p -> info;
            aux -> primf = aux -> seggerm = NULL;
            aux -> primf = copia_arbre(p -> primf);
            aux -> seggerm = copia_arbre(p -> seggerm);
        }
        catch (...) {
            destrueix_arbre(aux);
        }
    }
    return aux;
}

template <typename T>
void Arbre<T>::destrueix_arbre(node* p) throw() {
    if (p != NULL) {
        destrueix_arbre(p -> primf);
        destrueix_arbre(p -> seggerm);
        delete p;
    }
}

template <typename T>
Arbre<T>::Arbre(const T &x) {
    _arrel = new node;
    try {
        _arrel -> info = x;
        _arrel -> seggerm = NULL;
        _arrel -> primf = NULL;
    }
    catch (...) {
        delete _arrel;
        throw;
    }
}

template <typename T>
Arbre<T>::Arbre(const Arbre<T> &a) {
    _arrel = copia_arbre(a._arrel);
}

template <typename T>
Arbre<T>&  Arbre<T>::operator=(const Arbre<T> &a) {
    Arbre<T> tmp(a);
    node* aux = _arrel;
    _arrel = tmp._arrel;
    tmp._arrel = aux;
    return *this;
}

template <typename T>
Arbre<T>::~Arbre() throw() {
    destrueix_arbre(_arrel);
}

template <typename T>
void Arbre<T>::afegir_fill(Arbre<T> &a) {
    if (_arrel == NULL or a._arrel == NULL or
        a._arrel -> seggerm != NULL) {
        throw ArbreInvalid;
    }
    a._arrel -> seggerm = _arrel -> primf;
    _arrel -> primf = a._arrel;
    a._arrel = NULL;
}

// Llegeix un arbre general des de cin i el retorna.
Arbre<int> arbre() {
    int valor, nf;
    cin >> valor >> nf;
    Arbre<int> a(valor);
    stack<Arbre<int> > pa;
    while (nf>0) {
        pa.push(arbre());
        nf--;
    }
    while (not pa.empty()) {
        a.afegir_fill(pa.top());
        pa.pop();
    }
    return a;
}

int main() {
    int x;
    cin>>x;
    Arbre<int> a(arbre());
    a.preordre_especular();
    cout << endl;
}