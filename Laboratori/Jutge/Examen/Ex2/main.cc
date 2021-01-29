#include <sstream>
#include "solution.cpp"
using namespace std;

dicc::dicc() : _arrel(NULL) {}

dicc::~dicc() {
  esborra_nodes(_arrel);
}

void dicc::esborra_nodes(node* t) {
  if (t != NULL) {
    esborra_nodes(t->_esq);
    esborra_nodes(t->_cen);
    esborra_nodes(t->_dre);
    delete t;
  }
}

dicc::node::node(const char &c, node* esq, node* cen, node* dre) :
	_c(c), _esq(esq), _cen(cen), _dre(dre) {
}

typename dicc::node* dicc::insereix(node *t, nat i, const string &k) {
  if (t == NULL) {
    t = new node(k[i]);
    try {
      if (i < k.length()-1) {
        t->_cen = insereix(t->_cen, i+1, k);
      }
    }
    catch (...) {
      delete t;
      throw;
    }
  } else {
    if (t->_c > k[i]) {
      t->_esq = insereix(t->_esq, i, k);
    }
    else if (t->_c < k[i]) {
      t->_dre = insereix(t->_dre, i, k);
    }
    else { // (t->_c == k[i])
      t->_cen = insereix(t->_cen, i+1, k);
    }
  }
  return t;
}

void dicc::insereix (const string &k) {
  _arrel = insereix(_arrel, 0, k + '#'); // Símbol # és la marca de fi de clau
}

nat dicc::quantes_comencen(string inicials) const {
    nat sum = 0;
    for (nat i = 0; i< inicials.size();i++){
        sum += rconsulta(_arrel, inicials[i]);
    }
    return sum;
}

nat dicc::rconsulta(dicc::node *n, const char &c) const{
    if (n != NULL) {
        if (n->_c > c) {
            return rconsulta(n->_esq, c);
        }
        else if (n->_c < c) {
            return rconsulta(n->_dre, c);
        }
        else if (n->_c == c) {
            nat i = 0;
            rconsulta2(n->_cen, i);
            return i;
        }
    }
    return 0;
}

void dicc::rconsulta2(dicc::node *n, nat &i) const{
    if (n != NULL) {
        if(n->_c == '#') { i = i + 1; }
        rconsulta2(n->_esq, i);
        rconsulta2(n->_dre, i);
        rconsulta2(n->_cen, i);
    }
}


int main() {
  string input;
  dicc d;
  cin >> input;
  while (input != "----------") {
    d.insereix(input);
    cin >> input;
  }

  while (cin >> input) {
    cout << d.quantes_comencen(input) << " comencen per " << input << endl;
  }
  return 0;
}
