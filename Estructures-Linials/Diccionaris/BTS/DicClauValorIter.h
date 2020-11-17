////
//// Created by tonix on 17/11/2020.
////
//
//#ifndef ESIN_DICCLAUVALOR_H
//#define ESIN_DICCLAUVALOR_H
//
//#include <iostream>
//typedef unsigned int nat;
//using namespace std;
//
//template <typename Clau,typename Valor>
//class DicClauValor {
//private:
//
//    struct node {
//        Clau _k;
//        Valor _v;
//        node* _esq; // fill esquerre
//        node* _dret; // fill dret
//        node(const Clau &k, const Valor &v, node* esq = NULL, node* dret = NULL);
//    };
//    node *_arrel;
//
//    static node* consulta_bst(node *n, const Clau &k) throw();
//    static node* insereix_bst(node *n, const Clau &k, Valor &v) throw();
//    static node* elimina_bst(node *n, const Clau &k) throw();
//    static node* ajunta(node *t1, node* t2) throw();
//    static node* elimina_maxim(node *n) throw();
//
//public:
//    // Constructora per defecte. Crea un diccionari buit.
//    DicClauValor();
//
//    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
//    DicClauValor(const DicClauValor &d);
//    ~DicClauValor();
//    DicClauValor& operator=(const DicClauValor &d);
//
//    friend class iterador;
//    class iterador {
//    public:
//        friend class LlistaDobleEncadenada;
//
//        const Clau& operator*() const throw();
//
//        iterador& operator++() throw();
//        iterador operator++(int) throw();
//        iterador& operator--() throw();
//        iterador operator--(int) throw();
//        bool operator==(iterador it) const throw();
//        bool operator!=(iterador it) const throw();
//
//        static const int IteradorIndef = 330;
//    private:
//        iterador();
//        node* _p; // punter al node actual
//        node* _h;
//    };
//
//    void inserir_darrera(const Clau &k, const Valor &v, iterador it) throw();
//    void inserir_davant(const Clau &k, const Valor &v, iterador it) throw();
//
//    void esborrar_avnc(iterador& it) throw();
//    void esborrar_darr(iterador& it) throw();
//
//    void insereix(const Clau &k, const Valor &v) throw();
//    void elimina(const Clau &k) throw();
//
//    bool consulta(const Clau &k) const throw();
//    void consulta(const Clau &k, bool &hi_es, Valor &v) const throw();
//
//
//    // Retorna quants elements (claus) té el diccionari.
//    nat quants() const;
//
//    // Impressió per cout de claus del diccionari en ordre ascendent, separades per
//    // un espai, començant per ’[’ i acabant per ’]’, en dues versions:
//    // Imprimeix totes les claus
//    void print() const;
//    // Imprimeix les claus entre k1 i k2 ambdós incloses. Pre: k1 <= k2
//    void print_interval(const Clau &k1, const Clau &k2) const;
//
//    // Retorna la clau més petita i la més gran respectivament.
//    // Pre: El diccionari no està buit
//    Clau min() const;
//    Clau max() const;
//
//    // Retorna la clau de la posició i-èssima (comptant-les en ordre ascendent).
//    // Pre: El diccionari no està buit. 1 <= i <= quants()
//    Clau iessim(nat i) const;
//
//
//};
//
//
//#endif //ESIN_DICCLAUVALOR_H
