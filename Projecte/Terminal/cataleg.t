template<typename Valor>
    cataleg<Valor>::node_hash::node_hash(const string &k, const Valor &v, node_hash* seg): _k(k), _v(v), _seg(seg){}

/* Cost temporal: Constant O(1) */
template<typename Valor>
    int cataleg<Valor>::hash(const string &k) const {
    if(_M == 0) return 0;
    return static_cast<int>(h(k) % _M);
}

/* Cost temporal: Lineal O(n) */
template<typename Valor>
cataleg<Valor>::cataleg(nat numelems) throw(error){
    _quants = 0;
    _M = numelems;

    _taula = new node_hash*[_M];
    for (int i=0; i < _M; ++i) {
        _taula[i] = NULL;
    }
}

/* Cost temporal: Quadratic O(n²) */
template<typename Valor>
cataleg<Valor>::cataleg(const cataleg &c) throw(error) {
    _M = c._M;
    _quants = c.quants();

    _taula = new node_hash*[_M];
    for (int i=0; i < _M; ++i) {
        node_hash *aux = c._taula[i];
        node_hash *n;
        _taula[i] = n;

        while(aux != NULL){
            n = new node_hash(aux->_k, aux->_v);
            aux = aux->_seg;
            n = n->_seg;
        }
    }
}

/* Cost temporal: Lineal O(n) */
template<typename Valor>
    cataleg<Valor>::~cataleg() throw() {
    for (int i=0; i < _M; ++i) {
        auxDestr(_taula[i]);
    }
}

/* Cost temporal: Quadratic O(n²) */
template<typename Valor>
    cataleg<Valor>& cataleg<Valor>::operator=(const cataleg &c) throw(error) {
    cataleg<Valor> *d = new cataleg<Valor>(c._M);
    d->_quants = c.quants();

    for (int i=0; i < d->_M; ++i) {
        node_hash *aux = c._taula[i];
        node_hash *n;
        d->_taula[i] = n;

        while(aux != NULL){
            n = new node_hash(aux->_k, aux->_v);
            aux = aux->_seg;
            n = n->_seg;
        }
    }
    return *d;
}

/* Cost temporal: Lineal O( log(_quants) ) */
template<typename Valor>
    void cataleg<Valor>::assig(const string &k, const Valor &v) throw(error) {
    if(k.empty()) throw error(ClauInexistent);

    int i = hash(k);
    node_hash *p = _taula[i];

    bool hi_es = false;
    while (p != NULL and not hi_es) {
        if (p->_k == k)  hi_es = true;
        else  p = p->_seg;
    }
    if (hi_es) p->_v = v;
    else {
        _taula[i] = new node_hash(k, v, _taula[i]);
        ++_quants;
    }
}

/* Cost temporal: Lineal O( log(_quants) ) */
template<typename Valor>
    void cataleg<Valor>::elimina(const string &k) throw(error) {
    int i = hash(k);
    bool hi_es = false;
    node_hash *p = _taula[i], *ant = NULL;
    while (p != NULL and not hi_es) {
        if (p->_k == k) {
            hi_es = true;
        }else {
            ant = p;
            p = p->_seg;
        }
    }

    if(hi_es){
        if (ant == NULL) { _taula[i] = p->_seg; }
        else { ant->_seg = p->_seg; }
        delete p;
        p = NULL;
        --_quants;
    }
    else throw error(ClauInexistent);
}

/* Cost temporal: Lineal O( log(_quants) ) */
template<typename Valor>
    bool cataleg<Valor>::existeix(const string &k) const throw() {
    int i = hash(k);
    bool hi_es = false;
    node_hash* p = _taula[i];
    while (p != NULL and not hi_es) {
        if (p->_k == k) hi_es = true;
        else p = p->_seg;
    }
    return hi_es;
}

/* Cost temporal: Constant O(1) */
template<typename Valor>
    nat cataleg<Valor>::quants() const throw() {
    return _quants;
}

/* Cost temporal: Lineal O( log(_quants) ) */
template<typename Valor>
    Valor cataleg<Valor>::operator[](const string &k) const throw(error) {
    int i = hash(k);
    node_hash* p = _taula[i];
    while (p != NULL){
        if (p->_k == k) {
            return p->_v;
        }else {
            p = p->_seg;
        }
    }
    throw error(ClauInexistent);
}

/* Cost temporal: Lineal O(n) */
template<typename Valor>
    void cataleg<Valor>::auxDestr(const cataleg::node_hash *n) {
    if(n != NULL){
        auxDestr(n->_seg);
        delete n;
    }
}