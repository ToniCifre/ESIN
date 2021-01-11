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

bool is_in(vector< pair<int, int> > cami, int c){
    for(auto &p : cami){
        if(p.first == c) return true;
    }
    return false;
}

void cerca_cicles(mat g, vector< vector< nod > > &camins, vector< pair<int, int> > cami, int i, int prof) {
    if(prof > 1 ) {
        for(int j = 1; j < (int)g[i].size(); j++) {
            if(g[i][j] != 0 and !is_in(cami, j)){
                cami.emplace_back(j, g[i][j]);
                cerca_cicles(g, camins, cami, j, prof - 1 );
                cami.pop_back();
            }
        }
    }else{
        if(g[i][0] != 0){
            cami.emplace_back(0, g[i][0]);
            camins.push_back(cami);
        }
    }
}

int main() {
    int n;
    while (cin >> n) {
        mat g(n);
        llegir_graf(g, n);

        vector< vector< nod > > camins;
        vector< pair<int, int> > cami;
        cami.emplace_back(0, 0);

        cerca_cicles(g, camins, cami, 0, n);

        for(auto & camin : camins) {
            int sum = 0;
            for(auto & p : camin) {
                cout << p.first << " ";
                sum += p.second;
            }
            cout << "(" << sum << ")" << endl;
        }
        cout << "--------------------" << endl;
    }
}