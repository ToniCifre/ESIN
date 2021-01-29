#include "terminal.hpp"

#include <iostream>
using namespace std;
terminal::node::node(const nat &peus, const ubicacio &ubi, node* seg): _peus(peus), _ubi(ubi), _seg(seg){}

/*
 * Inicialitza la taula a null i la taula de forats l'inicialitza amb tots els llocs lliures.
 * Els dos catales els inicialitza amb una _M de n*m*h.
*/
terminal::terminal(nat n, nat m, nat h, terminal::estrategia st) throw(error) : _cataleg_ubicats(n*m*h), _area_espera(n*m*h){
    if(n < 1) throw error(NumFileresIncorr);
    if(m < 1) throw error(NumPlacesIncorr);
    if(h < 1 or h > HMAX) throw error(AlcadaMaxIncorr);
    if(st != FIRST_FIT and st != LLIURE) throw error(EstrategiaIncorr);
    _n = n;
    _m = m;
    _h = h;
    _estr = st;
    _ops = 0;

    _taula = new contenidor***[n];
    for(int x = 0; x < n; ++x) {
        _taula[x] = new contenidor**[m];
        for(int y = 0; y < m; ++y) {
            _taula[x][y] = new contenidor*[h];
            for(int z = 0; z < h; ++z) {
                _taula[x][y][z] = NULL;
            }
        }
    }

    _taula_forats = new node*[_n];
    for (int i=0; i < _n; ++i) {
        ubicacio u(i, 0, 0);
        _taula_forats[i] = new node(_m*10, u);
    }
}

/*
 * Crida a la funcio privada per inserir un contenidor, i en el cas que pugi inserir-ho
 * intentara inserir algun contenidor de la llista d'espera i en el cas que aquest es
 * tambés es pugi inserir tornara a començar des de l'inici de la llista.
 *
 * */
void terminal::insereix_contenidor(const contenidor &c) throw(error) {
    if(_cataleg_ubicats.existeix(c.matricula())){
        throw error(MatriculaDuplicada);
    }

    if(_insereix_contenidor(c)){
        list<string>::iterator it = _m_espera.begin();
        while(it != _m_espera.end()){
            if(_insereix_contenidor(_area_espera[*it])){
                it = _m_espera.begin();
            }else{
                it++;
            }
        }
    }
}

/*
 * En primer lloc, depenen de l'estrategia escollida, escollira una ubicació on poder inserir el
 * contenidor passat per parametre. si la ubicació no ha estat modificada, significa que no s'ha trobar
 * ninguna ubicació vàlida, de tal forma que el contenido s'introduira a la llista d'espera, en cas contrari,
 * s'introduira dintre de la terminal i es recalculara els espais disponibles de la fila modificada.
 *
 * Retorna un bool que indica si el contenidor s'ha pogut inserir a la terminal
 * */
bool terminal::_insereix_contenidor(const contenidor &c) throw(error){
    ubicacio u(-1,-1,-1);
    if (_estr == FIRST_FIT){
         _cerca_primera_ubicacio(u, c.longitud());
    }else{
        _cerca_millor_ubicacio(u, c.longitud());
    }

    if(u.placa() != -1){
        contenidor *cc = new contenidor(c);
        for(nat j=0; j<(c.longitud()/10); j++){
            _taula[u.filera()][u.placa()+j][u.pis()] = cc;
        }
        _cataleg_ubicats.assig(c.matricula(), u);

        if(_area_espera.existeix(c.matricula())){
            _elimina_espera(c.matricula());
        }

        cercar_forats(u.filera());
        _ops++;
    }else{
        if(!_area_espera.existeix(c.matricula())){
            _area_espera.assig(c.matricula(), c);
            _m_espera.push_front(c.matricula());
        }
    }
    return u.placa() != -1;

}

/*
 * Retorna la primera ubicació on el contenidor es igual o menor el tamany del forat disponible.
 *
 * Cost temporal: O( _n * _m )
 * */
void terminal::_cerca_primera_ubicacio(ubicacio &u, const nat peus){
    nat x = 0;
    bool trobat = false;
    while (!trobat and x < _n){
        node *n = _taula_forats[x];
        while (!trobat and n != NULL){
            if (n->_peus >= peus){
                u = n->_ubi;
                trobat = true;
            }
            n = n->_seg;
        }
        x++;
    }
}

/*
 * Intenta retornar la primera ubicació on el tamany del contenidor es igual al forat disponible,
 * en el cas que no existeixi un forat que cumpleixi aquest requisit tornara el espai més petit.
 *
 * Cost temporal: O( _n * _m )
 * */
void terminal::_cerca_millor_ubicacio(ubicacio &u, const nat peus){
    nat maxpeu = _m*10+1;

    nat x = 0;
    bool trobat = false;
    while (!trobat and x < _n){
        node *n = _taula_forats[x];
        while (!trobat and n != NULL){
            if(n->_peus == peus){
                u = n->_ubi;
                trobat = true;
            }else if(n->_peus < maxpeu and n->_peus > peus){
                u = n->_ubi;
                maxpeu = n->_peus;
            }
            n = n->_seg;
        }
        x++;
    }
}

/*
 *
 *
 * Cost temporal: O( log(_quants) + () )
 * */
void terminal::retira_contenidor(const string &m) throw(error) {
    if(!_area_espera.existeix(m)) {
        if (!_cataleg_ubicats.existeix(m)) throw error(MatriculaInexistent);

        ubicacio u = _cataleg_ubicats[m];
        list<string> l;
        _retira_contenidor(u, l);

        string m = l.back();
        for (list<string>::iterator it = l.begin(); it != l.end(); ++it){
            if(_cataleg_ubicats.existeix(*it)){
                ubicacio u = _cataleg_ubicats[*it];

                contenidor c = *_taula[u.filera()][u.placa()][u.pis()];

                if (m != *it) {
                    _area_espera.assig(c.matricula(), c);
                    _m_espera.push_front(c.matricula());
                }

                _cataleg_ubicats.elimina(c.matricula());

                delete _taula[u.filera()][u.placa()][u.pis()];
                for (nat i = 0; i < c.longitud() / 10; i++) {
                    _taula[u.filera()][u.placa() + i][u.pis()] = NULL;
                }

                _ops++;
            }
        }

        cercar_forats(u.filera());

        list<string>::iterator it = _m_espera.begin();
        while(it != _m_espera.end()){
            if(_insereix_contenidor(_area_espera[*it])){
                it = _m_espera.begin();
            }else{
                it++;
            }
        }
    }else{
        _elimina_espera(m);
    }
}

/*
 * A partir d'una ubicació inicial crea un recorregut en profunditat als contenidors que te asobre.
 *
 * Cost temporal: O( n * log(_quants) )
 * */
void terminal::_retira_contenidor(const ubicacio &u, list<string> &l){
    if(_taula[u.filera()][u.placa()][u.pis()] != NULL) {
        l.push_front(_taula[u.filera()][u.placa()][u.pis()]->matricula());
        if(u.pis() + 1 < _h){
            for (int i = u.placa() + _taula[u.filera()][u.placa()][u.pis()]->longitud() / 10 -1; i >= u.placa(); i--) {
                if (_taula[u.filera()][i][u.pis() + 1] != NULL) {

                    _retira_contenidor(_cataleg_ubicats[_taula[u.filera()][i][u.pis() + 1]->matricula()], l);
                }
            }
        }
    }
}

/*
 * Elimina un contenidor del cataleg i de la llista que guarda l'ordre d'insercións dels contenidors
 *
 * Cost temporal: Constant O( log(_quants) + n )
 * */
void terminal::_elimina_espera(const string &m){
    _area_espera.elimina(m);

    bool trobat = false;
    list<string>::iterator it = _m_espera.begin();
    while (it != _m_espera.end() and !trobat){
        if(*it == m){
            _m_espera.erase(it);
            trobat = true;
        }
        ++it;
    }
}

/*
 * Retorna la ubicació a partir de la matricula utilitzant els catalegs.
 * Retorna la ubicació del contenidor si es troba dintre de la termina,
 * en cas d'estar dintre de la llista d'espera retorna (-1, 0, 0)
 * i en cas de no existir retorna (-1, -1, -1).
 *
 * Cost temporal: Constant O( log(_quants) + log(_quants) )
 * */
ubicacio terminal::on(const string &m) const throw() {
    if(_cataleg_ubicats.existeix(m)){
        return _cataleg_ubicats[m];
    }else if(_area_espera.existeix(m)){
        return ubicacio(-1, 0, 0);
    }else{
        return ubicacio(-1, -1, -1);
    }
}

/*
 * Retorna la longitud del contenidor utilitzant els dos catalegs.
 * En el cas de que el contenidor no existeixi, llançara un error.
 *
 * Cost temporal: Constant O( log(_quants) + log(_quants) )
 * */
nat terminal::longitud(const string &m) const throw(error) {
    if(_cataleg_ubicats.existeix(m)){
        ubicacio u(_cataleg_ubicats[m]);
        return _taula[u.filera()][u.placa()][u.pis()]->longitud();
    }else if(_area_espera.existeix(m)){
        return _area_espera[m].longitud();
    }
    throw error(MatriculaInexistent);
}

/*
 * Insereix la matricula del contenidor al parametr m a partir de la ubicació pasada per parametre.
 * En el cas de no existir retorna el strign buit.
 * En el cas de ser uni ubicació de fora del terminal llança un error.
 *
 * Cost temporal: O(1)
 * */
void terminal::contenidor_ocupa(const ubicacio &u, string &m) const throw(error) {
    if(u.filera() < 0 or u.filera() >= _n or u.placa() < 0 or u.placa() >= _m or u.pis() < 0 or u.pis() >= _h){
        throw error(UbicacioNoMagatzem);
    }

    if(_taula[u.filera()][u.placa()][u.pis()] != NULL){
        m = _taula[u.filera()][u.placa()][u.pis()]->matricula();
    } else m = "";
}

/*
 * Reccor una filera determinada del terminal buscant els espais lliure d'intre d'aquest.
 * Si dus ubicacións tenen la mateiza altura es sumen els peus en el mateix node, i el el cas que
 * tingin altures diferentes es crea un nou node determinant que hi ha un altre espai buit.
 *
 * Antes de començar, elimina tots els elements anteriorment creats.
 *
 * Cost temporal: O( _m * _h )
 * */
void terminal::cercar_forats(const nat i){
    node *n = _taula_forats[i];
    while (n != NULL){
        node *aux = n;
        n = n->_seg;
        delete aux;
    }

    ubicacio u(-1,-1,-1);
    n = new node(10, u);
    _taula_forats[i] = n;

    int ant_k = -1;
    for(nat j = 0; j < _m; j++) {
        nat k = 0;
        bool buit = false;
        while (!buit and k < _h) {
            if (_taula[i][j][k]==NULL) buit = true;
            else k++;
        }
        if (buit) {
            if (k != ant_k) {
                ubicacio u(i, j, k);
                n->_seg = new node(10, u);
                n = n->_seg;
            } else {
                n->_peus = n->_peus + 10;
            }
        }
        ant_k = k;
    }

    node *aux = _taula_forats[i];
    _taula_forats[i] = _taula_forats[i]->_seg;
    delete aux;
}

/*
 * Recor tota la taula de forats cercant els espais lliure amb el tamany de 10 peus i
 * retorna la seva suma.
 *
 * Cost temporal: O( _n * _m ) */
nat terminal::fragmentacio() const throw() {
    nat frag = 0;
    for(nat i= 0; i< _n; i++) {
        node *n = _taula_forats[i];
        while (n != NULL){
            if(n->_peus == 10){
                frag++;
            }
            n = n->_seg;
        }
    }
    return frag;
}

/*
 * Retorna la llista de matricules dels contenidors que estan dintre de la llista d'espera.
 *
 * Cost temporal: O( 1 )*/
void terminal::area_espera(list<string> &l) const throw() {
    l = _m_espera;
    l.sort();
}

/* Cost temporal: Constant O(1) */
nat terminal::ops_grua() const throw() {
    return _ops;
}

/* Cost temporal: Constant O(1) */
nat terminal::num_fileres() const throw() {
    return _n;
}

/* Cost temporal: Constant O(1) */
nat terminal::num_places() const throw() {
    return _m;
}

/* Cost temporal: Constant O(1) */
nat terminal::num_pisos() const throw() {
    return _h;
}

/* Cost temporal: Constant O(1) */
terminal::estrategia terminal::quina_estrategia() const throw() {
    return _estr;
}

terminal::terminal(const terminal &b) throw(error) :_cataleg_ubicats(b.num_fileres()*b.num_places()*b.num_pisos()), _area_espera(b.num_fileres()*b.num_places()*b.num_pisos()) {
    _n = b._n;
    _m = b._m;
    _h = b._h;
    _ops = b._ops;
    _estr = b._estr;

    _taula = new contenidor***[_n];
    for(int x = 0; x < _n; ++x) {
        _taula[x] = new contenidor**[_m];
        for(int y = 0; y < _m; ++y) {
            _taula[x][y] = new contenidor*[_h];
            for(int z = 0; z < _h; ++z) {
                contenidor c(b._taula[x][y][z]->matricula(), b._taula[x][y][z]->longitud());
                _taula[x][y][z] = b._taula[x][y][z];
            }
        }
    }

    node *n;
    _taula_forats = new node*[_n];
    for (int i=0; i < _n; ++i) {
        node *aux;
        _taula_forats[i] = aux;
        n = b._taula_forats[i];
        while (n!=NULL){
            aux = new node(n->_peus, n->_ubi);
            n = n->_seg;
            aux = aux->_seg;
        }
    }

    _cataleg_ubicats = b._cataleg_ubicats;
}

terminal &terminal::operator=(const terminal &b) throw(error) {
    return *this;
}

/* Cost temporal: Cubic O(_n * _h * _m) */
terminal::~terminal() throw() {
    for(int x = 0; x < _n; ++x) {
        for(int z = 0; z < _h; ++z) {
            for(int y = 0; y < _m; ++y) {
                if(_taula[x][y][z] != NULL) {
                    y = y + _taula[x][y][z]->longitud()/10-1;
                    delete _taula[x][y][z];
                }
            }
        }
    }

}
