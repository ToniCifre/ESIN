//
// Created by tonix on 02/11/2020.
//
// Elements del nivell n-èssim d'un arbre general
//

#include <iostream>
#include <cstdlib>
using namespace std;
typedef unsigned int nat;

template <typename T>
class Arbre {

public:
    // Construeix un Arbre format per un únic node que conté a x.
    Arbre(const T &x);

    // Tres grans.
    Arbre(const Arbre<T> &a);
    Arbre& operator=(const Arbre<T> &a);
    ~Arbre() throw();

    // Col·loca l’Arbre donat com a darrer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
    void afegir_darrer_fill(Arbre<T> &a);

    static const int ArbreInvalid = 400;

    // Escriu una línia amb els elements del nivell i, d’esquerra a dreta.
    // Cada element ha de sortir precedit d’un espai.
    void nivell(nat i) const;

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

    void nivell(nat i, node *p) const;
};

template <typename T>
void Arbre<T>::nivell(nat i, node *p) const{
    if(p != NULL){
        if(i == 0){
            cout <<" "<<p->info;
        }else if (i > 0){
            nivell(i-1, p->primf);
        }
        if (i >= 0){
            nivell(i, p->seggerm);
        }
    }
}

template <typename T>
void Arbre<T>::nivell(nat i) const{
    nivell(i, _arrel);
}
