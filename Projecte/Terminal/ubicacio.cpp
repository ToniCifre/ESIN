#include "ubicacio.hpp"

/* Constructora. Crea la ubicació <i, j, k>. Genera un error si
   <i, j, k> no pertany a {<u, v, w> | u >= 0 ^ v >= 0 ^ w >= 0}
    o a {<-1, 0, 0>,  <-1,-1,-1>}.
    Cost temporal: Constant O(1).
    Cost espacial: Constant O(1).*/
ubicacio::ubicacio(int i, int j, int k) throw(error) {
    if((i > -1 && j > -1 && k > -1) || (i == -1 && j == -1 && k == -1) || (i == -1 && j == 0 && k == 0)){
        _fil = i;
        _pla = j;
        _pis = k;
    }
    else{
        throw error(UbicacioIncorrecta);
    }
}

/* Constructora per còpia, assignació i destructora.
   Cost temporal: Constant O(1)
   Cost espacial: Constant O(1)*/
ubicacio::ubicacio(const ubicacio &u) throw(error) {
    _fil = u._fil;
    _pla = u._pla;
    _pis = u._pis;
}

/*Cost temporal: Constant O(1)
Cost espacial: Constant O(1)*/
ubicacio &ubicacio::operator=(const ubicacio &u) throw(error) {
    _fil = u._fil;
    _pla = u._pla;
    _pis = u._pis;
    return *this;
}

ubicacio::~ubicacio() throw(){}

/* Consultors. Retornen respectivament el primer, segon i tercer
     component de la ubicació.
   Cost temporal: Constant O(1)
   Cost espacial: Constant O(1)*/
int ubicacio::filera() const throw() {
    return _fil;
}

/*Cost temporal: Constant O(1)
Cost espacial: Constant O(1)*/
int ubicacio::placa() const throw() {
    return _pla;
}

/*Cost temporal: Constant O(1)
Cost espacial: Constant O(1)*/
int ubicacio::pis() const throw() {
    return _pis;
}

/* Operadors de comparació.
   Cost temporal: Constant O(1)
   Cost espacial: Constant O(1)*/
bool ubicacio::operator==(const ubicacio &u) const throw() {
    bool iguals = false;
    if(_fil == u._fil && _pla == u._pla && _pis == u._pis) iguals = true;
    return iguals;
}

/*Cost temporal: Constant O(1)
Cost espacial: Constant O(1)*/
bool ubicacio::operator!=(const ubicacio &u) const throw() {
    return !(*this == u);
}

/*Cost temporal: Constant O(1)
Cost espacial: Constant O(1)*/
bool ubicacio::operator<(const ubicacio &u) const throw() {
    bool menor = false;
    if(_fil < u._fil) menor = true;
    else if(_fil == u._fil){
        if(_pla < u._pla) menor = true;
        else if(_pla == u._pla){
            if(_pis < u._pis) menor = true;
        }
    }
    return menor;
}

/*Cost temporal: Constant O(1)
Cost espacial: Constant O(1)*/
bool ubicacio::operator<=(const ubicacio &u) const throw() {
    return (*this < u || *this == u);
}

/*Cost temporal: Constant O(1)
Cost espacial: Constant O(1)*/
bool ubicacio::operator>(const ubicacio &u) const throw() {
    return !(*this <= u);
}

/*Cost temporal: Constant O(1)
Cost espacial: Constant O(1)*/
bool ubicacio::operator>=(const ubicacio &u) const throw() {
    return !(*this < u);
}
