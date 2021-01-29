//
// Created by tonix on 10/01/2021.
//

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, string> ArcP;
typedef vector< pair< vector<ArcP> , string> > GrafP;
void leer_tripletes(GrafP &G, int m) {
    string aux;
    ArcP arco;
    for (int i = 0; i < m; i++) {
        cin >> aux >> arco.second;
        arco.first = 0;
        G[aux].first.push_back(arco);
        G[aux].second = arco.second;
    }
}

int main() {
    int n;
    int m;
    while (cin >> n >> m) {
        GrafP G(n);
        leer_tripletes(G, m);
        for(auto &y : G) {
            cout << y.second << endl;
        }
    }
}