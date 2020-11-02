//
// Created by tonix on 02/11/2020.
//
// Arbre binari. Elements del nivell n-èssim
//

#include <iostream>
#include <cstdlib>
using namespace std;
typedef unsigned int nat;

template <typename T>
class Abin {
public:
    Abin(): _arrel(NULL) {};
    // Pre: cert
    // Post: el resultat és un arbre sense cap element
    Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
    // Pre: cert
    // Post: el resultat és un arbre amb un element i dos subarbres

    // Les tres grans
    Abin(const Abin<T> &a);
    ~Abin();
    Abin<T>& operator=(const Abin<T>& a);

    // Escriu una línia amb els elements del nivell i-èssim, d’esquerra
    // a dreta. Cada element ha de sortir precedit d’un espai.
    void nivell(nat i) const;

private:
    struct node {
        node* f_esq;
        node* f_dret;
        T info;
    };
    node* _arrel;
    static node* copia_nodes(node* m);
    static void esborra_nodes(node* m);

    static void nivell(nat i, node* p);
};

template <typename T>
void Abin<T>::nivell(nat i, node *p) {
    if(p != NULL){
        if(i == 0){
            cout <<" "<<p->info;
        }else if (i > 0){
            nivell(i-1, p->f_esq);
            nivell(i-1, p->f_dret);
        }
    }
}

template <typename T>
void Abin<T>::nivell(nat i) const{
    return nivell(i, _arrel);
}
