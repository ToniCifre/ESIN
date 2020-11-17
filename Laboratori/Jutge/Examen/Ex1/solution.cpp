//
// Created by tonix on 17/11/2020.
//
#include "llista.hpp"
void Llista::fusiona_suma(Llista &l2, nat n) {
    // El const en funció de l1 i l2 es la suma del tamany de les dues llistes per 2 en els pitjors dels casos
    // es a dir, (l2.size + l2.size) * 2
    // Cost = 2n

    node *x1 = _prim;
    node *x2 = l2._prim->seg;
    l2._prim->seg = NULL;
    l2._long = 1;
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
                    ++_long;
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
        ++_long;
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