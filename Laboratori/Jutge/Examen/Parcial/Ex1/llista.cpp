#include <iostream>
#include "llista.hpp"

Llista::Llista() : _long(0) {
  _prim = new node;
  _prim->seg = NULL;
}

Llista::Llista(const vector<int> &v) : _long(v.size()) {
  _prim = new node;
  _prim->seg = NULL;
  node *p, *pant = _prim;
  for (int i=0; i<v.size(); i++) {
    p = new node;
    p->info = v[i];
    p->seg = NULL;
    pant->seg = p;
    pant = p;
  }
}

Llista::~Llista() {
  node *p = _prim, *pelim;
  while (p != NULL) {
    pelim = p;
    p = p->seg;
    delete pelim;
  }
}

nat Llista::longitud() const {
  return _long;
}

void Llista::mostra() const {
  node *p = _prim->seg;
  cout << "[";
  if (p != NULL) {
    cout << p->info;
    p = p->seg;
  }
  while (p != NULL) {
    cout << " " << p->info;
    p = p->seg;
  }
  cout << "]" << endl;
}


void Llista::fusiona_suma(Llista &l2, nat n) {
    // El const en funció de l1 i l2 es la suma del tamany de les dues llistes per 2 en els pitjors dels casos
    // es a dir, (l2.size + l2.size) * 2
    // Cost = 2n

    node *x1 = _prim;
    node *x2 = l2._prim->seg;
    l2._prim->seg = NULL;
    int sum = 0;

    while (x1 != NULL) {
        for (int i = 0; i < n; ++i) {
            if(x1->seg != NULL) {
                x1 = x1->seg;
            }
        }
        if(x1->seg == NULL) {
            break;
        }else{
            for (int i = 0; i < n; ++i) {
                if(x2 != NULL) {
                    node *aux = x2->seg;
                    x2->seg = x1->seg;
                    x1->seg = x2;

                    x1 = x1->seg;
                    x2 = aux;
                }
            }
        }
    }

    while (x2 != NULL) {
        node *aux = x2->seg;
        x2->seg = x1->seg;
        x1->seg = x2;

        x1 = x1->seg;
        x2 = aux;
    }
    x1 = _prim->seg;
    while (x1 != NULL) {
        sum = sum + x1->info;
        x1 = x1->seg;
    }
    node *p = new node();
    p->seg = _prim->seg;
    p->info = sum;
    _prim->seg = p;

}