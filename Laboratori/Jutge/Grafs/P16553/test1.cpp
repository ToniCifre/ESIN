//
// Created by tonix on 10/01/2021.
//

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef vector< vector<int> > GrafP;


int const INFINITY = numeric_limits<int>::max();




void leer_tripletes(GrafP &G, int m) {
    int x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        G[x].push_back(y);
    }
}


bool is_in(vector< int > cami, int c){
    for(auto &p : cami){
        if(p == c) return true;
    }
    return false;
}

void DFS(const GrafP &g, vector< int > &cami, int i) {
    for(auto &n : g[i]) {
        if(!is_in(cami, n)){
            cami.push_back(n);
            DFS(g, cami, n);
        }
    }
}

void DFSI(const GrafP &g, vector< int > &cami, int i) {
    for(auto &n : g[i]) {
        if(!is_in(cami, n)){
            DFS(g, cami, n);
            cami.push_back(n);
        }
    }
}

void BFS(const GrafP &g, vector< int > &cami, int i) {
    vector<int> aux(g[i].size());
    for(auto &n : g[i]) {
        if(!is_in(cami, n)){
            cami.push_back(n);
            aux.push_back(n);
        }
    }
    for(auto &n : aux) {
        DFS(g, cami, n);
    }
}

int main() {
    int n;
    int m;
    while (cin >> n >> m) {
        GrafP G(n);
        leer_tripletes(G, m);

        vector< int > cami;
        cami.push_back(0);
        DFS(G, cami, 0);

        vector< int > cami2;
        DFSI(G, cami2, 0);
        cami2.push_back(0);

        vector< int > cami3;
        cami3.push_back(0);
        BFS(G, cami3, 0);

        for(auto & p : cami) {
            cout << p << " ";
        }
        cout << endl;
        for(auto & p : cami2) {
            cout << p << " ";
        }
        cout << endl;
        for(auto & p : cami3) {
            cout << p << " ";
        }
        cout << endl;

    }
}