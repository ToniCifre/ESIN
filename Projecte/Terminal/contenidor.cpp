#include "contenidor.hpp"

/*Cost temporal: Constant O(1) */
contenidor::contenidor(const string &m, nat l) throw(error) {
    if (!_valida_matricula(m)) throw error(MatriculaIncorrecta);
    if (!_valida_longitud(l)) throw error(LongitudIncorrecta);
    _m = m;
    _l = l;
}

/*Cost temporal: Lineal O(n) */
bool contenidor::_valida_matricula(const string &m) {
    if (m.empty()) return false;
    for(nat i = 0; i < m.length(); i++){
        if(!isupper(m[i]) and !isdigit(m[i])) {
            return false;
        }
    }
    return true;
}

/*Cost temporal: Constant O(1) */
bool contenidor::_valida_longitud(const nat &l) {
    if( l == 10 or l == 20 or l == 30) return true;
    return false;
}

/*Cost temporal: Constant O(1) */
contenidor::contenidor(const contenidor &u) throw(error) {
    _m = u.matricula();
    _l = u.longitud();
}

contenidor::~contenidor() throw() {
}

/*Cost temporal: Constant O(1) */
contenidor &contenidor::operator=(const contenidor &u) throw(error) {
    _m = u.matricula();
    _l = u.longitud();
    return *this;
}

/*Cost temporal: Constant O(1) */
nat contenidor::longitud() const throw() {
    return _l;
}

/*Cost temporal: Constant O(1) */
string contenidor::matricula() const throw() {
    return _m;
}

/*Cost temporal: Constant O(1) */
bool contenidor::operator==(const contenidor &c) const throw() {
    return _m == c._m and _l == c._l;
}

/*Cost temporal: Constant O(1) */
bool contenidor::operator!=(const contenidor &c) const throw() {
    return _m != c._m or _l != c._l;
}

/*Cost temporal: Constant O(1) */
bool contenidor::operator<(const contenidor &c) const throw() {
    if (_m == c._m) return _l < c._l;
    return _m < c._m;
}

/*Cost temporal: Constant O(1) */
bool contenidor::operator<=(const contenidor &c) const throw() {
    if (_m == c._m) return _l <= c._l;
    return _m <= c._m;
}

/*Cost temporal: Constant O(1) */
bool contenidor::operator>(const contenidor &c) const throw() {
    if (_m == c._m) return _l > c._l;
    return _m > c._m;
}

/*Cost temporal: Constant O(1) */
bool contenidor::operator>=(const contenidor &c) const throw() {
    if (_m == c._m) return _l >= c._l;
    return _m >= c._m;
}
