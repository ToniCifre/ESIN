//
// Created by tonix on 02/11/2020.
//

#include <iostream>
using namespace std;


bool es_capicua(int n);


int main() {
    int n;
    while (cin >> n) cout << (es_capicua(n) ? "true" : "false") << endl;
}
