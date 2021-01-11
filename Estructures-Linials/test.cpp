#include <iostream>
//#include <esin/util>
//#include "Pila.cpp"
#include "Graf/graf.h"
#include "Graf/LlistaIterator.h"

typedef unsigned int nat;
using namespace std;


int main() {
    std::cout << "Hello, World!" << std::endl;

    graf<int, int> g;
    g.afegeix_vertex(1);
    g.afegeix_vertex(2);
    g.afegeix_vertex(3);

//    LlistaIterator<string , int> l;
//    l.inserir("1",1);
//    l.inserir("2",2);
//    l.inserir("3",3);
//    l.inserir("4",4);
//    l.inserir("5",5);
//    l.inserir("6",6);
//    l.mostra();


//    CuaPrio<int, int> c;
//    c.insereix(13, 13);
//    c.insereix(2, 2);
//    c.insereix(5, 5);
//    c.insereix(27, 27);
//    c.insereix(8, 8);
//    c.insereix(15, 15);
//    c.insereix(10, 10);
//    c.insereix(4, 4);
//    c.DFS(1);
//    cout<<c.max()<<endl;
//
//    int myNum[6] = {10, 20, 30, 52, 11, 12};
//    heap_sort(myNum, 6);
//    cout<<"ordenat"<<endl;
//    for(auto n : myNum){
//        cout << n << endl;
//    }


//    diccDigital<char,string,string> d;
//    d.insereix("toni", "toni");
//    string t = "";
//    bool b = false;
//    d.consulta("toni", b, t);
//    std::cout << t << std::endl;
//    std::cout << b << std::endl;


//    Pila<int> p;
//    for(int i = 0; 10> i; i++){
//        p.apilar(i);
//    }
//    for(int i = 0; 10> i; i++){
//        p.desapilar();
//    }


//    string t = util::tostring(2);
//    std::cout << t << std::endl;
//
//    util::Hash<string> h;
//    unsigned long i = h("toni cifres jklsdhf gjsdhf gklhsdfkl vicena");
//    std::cout << i << std::endl;

    return 0;
}
