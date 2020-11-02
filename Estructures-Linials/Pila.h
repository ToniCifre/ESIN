//
// Created by tonix on 05/10/2020.
//

#ifndef ESIN_Pila_H
#define ESIN_Pila_H

template <typename T>
class Pila {

public:
    Pila() throw();
    Pila(const Pila<T> &p) throw();
    ~Pila() throw();

    Pila<T>& operator=(const Pila<T> &p) throw();
    Pila<T> operator&(const T &x) const throw();

    void apilar(const T &x) throw();
    void desapilar() throw();

    const T& cim() const throw();

    bool es_plena() const throw();
    bool es_buida() const throw();

    Pila<T> resta() const throw();

    static const int PilaBuida = 300;
    static const int PilaPlena = 301;
    static const int MAX = 3;

private:
    T _taula[MAX];
    int _pl;
    void copiar(const Pila<T> &p) throw();

};
#endif
