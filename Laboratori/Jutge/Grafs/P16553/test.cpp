//
// Created by tonix on 10/01/2021.
//
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> row;
typedef vector<row> mat;
typedef pair<int, int> nod;


void llegir_graf(mat& g, int m) {
    int x;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cin >> x;
            g[i].push_back(x);
        }
    }
}

bool is_in(vector< int > cami, int c){
    for(auto &p : cami){
        if(p == c) return true;
    }
    return false;
}

void DFS(const mat &g, vector< int > &cami, int i) {
    for(int j = 0; j < (int)g.size(); j++) {
        if(g[i][j] != 0 and !is_in(cami, j)){
            cami.push_back(j);
            DFS(g, cami, j);
        }
    }

}

void DFSI(const mat &g, vector< int > &cami, int i) {
    for(int j = 0; j < (int)g.size(); j++) {
        if(g[i][j] != 0 and !is_in(cami, j)){
            DFS(g, cami, j);
            cami.push_back(j);
        }
    }

}

int main() {
    int n;
    while (cin >> n) {
        mat g(n);
        llegir_graf(g, n);

        vector< int > cami;

        DFSI(g, cami, 0);
        cami.push_back(0);

        for(auto & p : cami) {
            cout << p << " ";
        }
        cout << endl;
    }
}