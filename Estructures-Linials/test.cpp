#include <iostream>
#include "Pila.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Pila<int> p;
    for(int i = 0; 10> i; i++){
        p.apilar(i);
    }
    for(int i = 0; 10> i; i++){
        p.desapilar();
    }
    return 0;
}
