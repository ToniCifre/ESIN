//
// Created by tonix on 05/11/2020.
//
// Nombre de nodes amb els dos subarbres buits d'un arbre binari
//

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

    // Retorna el nombre de nodes amb els dos subarbres buits
    nat nodes_subarbres_buits() const;

private:
    struct node {
        node* f_esq;
        node* f_dret;
        T info;
    };
    node* _arrel;
    static node* copia_nodes(node* m);
    static void esborra_nodes(node* m);

    // Aquí va l’especificació dels mètodes privats addicionals
    nat nodes_subarbres_buits(node* n, nat n_fulles) const;
};

// Aquí va la implementació del mètode nodes_subarbres_buits
template <typename T>
nat Abin<T>::nodes_subarbres_buits(node *n, nat n_fulles) const{
    if(n != NULL){
        if(n->f_esq != NULL){
            n_fulles = nodes_subarbres_buits(n->f_esq, n_fulles);
        }if(n->f_dret != NULL){
            n_fulles = nodes_subarbres_buits(n->f_dret, n_fulles);
        }if(n->f_esq == NULL and n->f_dret == NULL){
            ++n_fulles;
        }
    }
    return n_fulles;
}

template <typename T>
nat Abin<T>::nodes_subarbres_buits() const{
    return nodes_subarbres_buits(_arrel, 0);
}