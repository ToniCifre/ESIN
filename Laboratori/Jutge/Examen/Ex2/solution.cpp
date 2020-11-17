//
// Created by tonix on 17/11/2020.
//

#include "abin.cpp"
template<typename T>
list<T> Abin<T>::preordre_especular() const {
    // cost = 2^n
    list<int> l;
    preordre_especular_iter(_arrel, l);
    return l;
}

template<typename T>
void Abin<T>::preordre_especular_iter(Abin::node *n, list<T> & lpre) {
    if (n != NULL) {
        lpre.push_back(n->info);
        if (!n->thread_dret) preordre_especular_iter(n->f_dret, lpre);
        if (!n->thread_esq) preordre_especular_iter(n->f_esq, lpre);
    }
};
