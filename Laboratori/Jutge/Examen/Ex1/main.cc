#include <iostream>
using namespace std;
#include "solution.cpp"

graf::graf() : n(0), m(0) {}

graf::~graf() {}

void graf::llegeix() {
  // Llegim el nombre de vèrtexs i arestes
  cin >> n >> m;

  // Creem les llistes d'adjacència (vectors amb els successors dels n vèrtexs)
  a = vector<vector<nat> >(n);

  // Llegim les m arestes
  nat u, v;
  for(nat i = 0; i < m; i++) {
    cin >> u >> v; // Aresta que connecta vèrtex u amb vèrtex v
    a[u].push_back(v);
  }
}

bool graf::DFS(const vector<vector<nat> > &g, vector< bool > &cami, nat ini, nat fi) const {
    //Cost = n*n
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
    //Cost = n*n
    if(ini == fi) return true;
    vector< bool > cami(n,false);
    cami[ini] = true;
    return DFS(a, cami, ini, fi);
};

int main() {
  graf g;
  g.llegeix();
  nat ini, fi;
  while (cin >> ini >> fi) {
    if (g.hi_ha_cami(ini, fi))
      cout << "SI hi ha camí de " << ini << " a " << fi << endl;
    else
      cout << "NO hi ha camí de " << ini << " a " << fi << endl;
  }
  return 0;
}
