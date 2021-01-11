//
// Created by tonix on 11/01/2021.
//

#ifndef ESIN_CUAPRIO_H
#define ESIN_CUAPRIO_H
#include "esin/error"

typedef unsigned int nat;
using namespace std;

template <typename Elem, typename Prio>
class CuaPrio {
public:
    CuaPrio();
    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
    CuaPrio(const CuaPrio &d);
    ~CuaPrio();

    void insereix(const Elem &x, const Prio &p) throw(error);

    Elem min() const throw(error);
    Elem max() const throw(error);
    Prio prio_min() const throw(error);

    void elim_min() throw(error);
    void elim_max() throw(error);

    void DFS(nat j);


    static const int CuaPrioPlena = 310;
    static const int CuaPrioBuida = 320;
private:
    static const nat MAX_ELEM = 100;
    nat _nelems;

    pair<Elem, Prio> _h[MAX_ELEM+1];

    void enfonsar(nat j) throw();
    void enfonsarI(nat p) throw();

    void surar(nat p) throw();
};


template<typename Elem, typename Prio>
CuaPrio<Elem, Prio>::CuaPrio(): _nelems(0) {}

template<typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::insereix(const Elem &x, const Prio &p) throw(error) {
    if (_nelems == MAX_ELEM){
        cout<<"nelem igual max elem en inser function"<<endl;
    }else{
        ++_nelems;
        _h[_nelems] = make_pair(x, p);
        surar(_nelems);
    }
}

template<typename Elem, typename Prio>
Elem CuaPrio<Elem, Prio>::min() const throw(error) {
    if (_nelems != 0) {
        return _h[1].first;
    }
}
template<typename Elem, typename Prio>
Elem CuaPrio<Elem, Prio>::max() const throw(error) {
    if (_nelems != 0) {
        return _h[_nelems].first;
    }
}

template<typename Elem, typename Prio>
Prio CuaPrio<Elem, Prio>::prio_min() const throw(error) {
    if (_nelems == 0) throw error(CuaPrioBuida);
    return _h[1].second;
}

template<typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::elim_min() throw(error) {
    if (_nelems != 0){
        swap(_h[1], _h[_nelems]);
        --_nelems;
        enfonsar(1);
    };
}

template<typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::elim_max() throw(error) {
    if (_nelems != 0){
        --_nelems;
    };
}

template<typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::enfonsar(nat j) throw() {
    nat hj;
    // si j no té fill esquerre ja hem acabat
    if (2*j <= _nelems) {
        hj = 2*j;
        if (hj < _nelems and
            _h[hj].second > _h[hj+1].second) {
            ++hj;
        }
        // hj apunta al fill de mínima prioritat de j.
        // Si la prioritat de j és major que la prioritat del
        // seu fill menor cal intercanviar i seguir enfonsant.
        if (_h[j].second > _h[hj].second) {
            swap(_h[j], _h[hj]);
            enfonsar(hj);
        }
    }
}

template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::enfonsarI(nat p) throw() {
    bool fi = false;
    while ((2*p <= _nelems) and not fi) {
        nat hj = 2*p;
        if (hj < _nelems and
            _h[hj].second > _h[hj+1].second) {
            ++hj;
        }
        if (_h[p].second > _h[hj].second) {
            swap(_h[p], _h[hj]);
            p = hj;
        }
        else {
            fi = true;
        }
    }
}

template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::surar(nat p) throw() {
    nat q;
    bool fi = false;
    while (p > 1 and not fi) {
        q = p / 2;
        if (_h[q].second > _h[p].second) {
            swap(_h[p], _h[q]);
            p = q;
        }
        else {
            fi = true;
        }
    }
}

template<typename Elem, typename Prio>
CuaPrio<Elem, Prio>::CuaPrio(const CuaPrio &d) {

}

template<typename Elem, typename Prio>
CuaPrio<Elem, Prio>::~CuaPrio() {

}

template<typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::DFS(nat j) {
    if (j <= _nelems) {
        cout<<_h[j].second<<" " <<_h[j].first <<" - ";
        DFS(2*j);
        DFS(2*j+1);
    }
}

template <typename T>
void heap_sort(T A[], nat n){
    CuaPrio<T, T> c;
    for (nat i=0; i < n; ++i) {
        c.insereix(A[i], A[i]);
    }
    for (int i=n-1; i >= 0; i--) {
        A[i] = c.min();
        c.elim_min();
    }
}

//Ordenació sense usar la classe CuaPrio.
template <typename T>
void heapsort(T A[], nat n) {
    for (nat i=n/2; i>0; --i) {
        enfonsar(A, n, i);
    }
    nat i=n;
    while (i > 0) {
        swap(A[1], A[i]);
        --i;
        enfonsar(A, i, 1);
    }
}

#endif //ESIN_CUAPRIO_H
