//
// Created by tonix on 05/11/2020.
//
// P1: Arbre general. Calcula arbre compta graus.
//

#include <cstdlib>
#include <string>
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

    // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
    void afegir_fill(Arbre<T> &a);

    // Imprimeix la informació dels nodes en preodre, cada element en una nova línia i
    // precedit per espais segons el nivell on està situat.
    void preordre() const;

    static const int ArbreInvalid = 400;

    // Modifica el contingut dels nodes per tal de guardar a cada node el seu grau
    void arbre_compta_graus();

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
    static void preordre(node *p, string pre);

    void arbre_compta_graus(node *n);
};

template<typename T>
void Arbre<T>::arbre_compta_graus() {
    arbre_compta_graus(_arrel);
}

template<typename T>
void Arbre<T>::arbre_compta_graus(node *n) {
    if(n != NULL){
        if(n->primf != NULL) arbre_compta_graus(n->primf);
        if(n->seggerm != NULL) arbre_compta_graus(n->seggerm);

        nat grau = 0;
        node *aux = n->primf;
        while (aux != NULL){
            aux = aux->seggerm;
            ++grau;
        }
        n->info = grau;
    }
}
