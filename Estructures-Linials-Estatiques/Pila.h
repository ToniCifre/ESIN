//
// Created by tonix on 05/10/2020.
//

#ifndef ESIN_Pila_H
#define ESIN_Pila_H
#include "error"
template <typename T>
class Pila {

public:
    Pila() throw(error);
    Pila(const Pila<T> &p) throw(error);
    ~Pila() throw();

    Pila<T>& operator=(const Pila<T> &p) throw(error);
    Pila<T> operator&(const T &x) const throw(error);

    void apilar(const T &x) throw(error);
    void desapilar() throw(error);

    const T& cim() const throw(error);

    bool es_plena() const throw();
    bool es_buida() const throw();

    Pila<T> resta() const throw(error);

    static const int PilaBuida = 300;
    static const int PilaPlena = 301;
    static const int MAX = 3;

private:
    T _taula[MAX];
    int _pl;
    void copiar(const Pila<T> &p) throw(error);

};
#endif
