//
// Created by tonix on 17/11/2020.
//

#include "vector"
using namespace std;
typedef unsigned int nat;

class graf {
    // Graf dirigit i no etiquetat.
    // Les arestes es guarden en llistes d’adjacència (vector amb els successors).
public:
    // Constructora per defecte. Crea un graf buit.
    graf();

    // Destructora
    ~graf();

    // Llegeix les dades del graf del canal d’entrada
    void llegeix();

    bool hi_ha_cami(nat ini, nat fi) const;
    // Pre: ini i fi són vèrtexs del graf (són menors que n)
    // Post: Retorna un booleà indicant si hi ha camí per anar d’ini a fi

private:
    nat n; // Nombre de vèrtexs
    nat m; // Nombre d’arestes
    vector<vector<nat> > a; // Vectors amb els successors de cada vèrtex

//    bool is_in(const vector< nat >& cami, nat c) const;
    bool DFS(const vector<vector<nat> > &g, vector< bool > &cami, nat ini, nat fi) const;
};


bool graf::DFS(const vector<vector<nat> > &g, vector< bool > &cami, nat ini, nat fi) const {
    //Cost = n+m
    for(auto &t : g[ini]) {
        if(t == fi) return true;
        if(!cami[t]){
            cami[t] = true;
            if(DFS(g, cami, t, fi))return true;
            cami[t] = false;
        }
    }
    return false;
}

bool graf::hi_ha_cami(nat ini, nat fi) const{
    //Cost = n+m
    if(ini == fi) return true;
    vector< bool > cami(n,false);
    cami[ini] = true;
    return DFS(a, cami, ini, fi);
};