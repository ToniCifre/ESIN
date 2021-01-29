#include <iostream>
#include <sstream>
#include "solution.cpp"

template <typename T>
deque<T>::deque() : _long(0) {
  _prim = NULL;
}

template <typename T>
deque<T>::deque(const deque &dq) : _long(dq._long) {
  _prim = NULL;
  node *p, *pant = NULL, *p2 = dq._prim;
  if (dq._prim != NULL) { // La deque no és buida
    while (p2 != dq._prim->ant) {
      p = new node;
      p->info = p2->info;
      p->ant = pant;
      if (pant == NULL)
        _prim = p;
      else
        pant->seg = p;
      pant = p;
      p2 = p2->seg;
    }
    // Creem el darrer node i el tanquem circularment
    p = new node;
    p->info = p2->info;
    if (pant == NULL) { // La deque només té 1 node
      p->ant = p;
      p->seg = p;
      _prim = p;
    } else {
      p->ant = pant;
      p->seg = _prim;
      pant->seg = p;
      _prim->ant = p;
    }
  }
}

template <typename T>
deque<T>::~deque() {
  if (_prim != NULL) {
    node *p = _prim->seg, *pelim;
    while (p != _prim) {
      pelim = p;
      p = p->seg;
      delete pelim;
    }
    delete p;
  }
}

template <typename T>
nat deque<T>::size() const {
  return _long;
}

template <typename T>
bool deque<T>::empty() const {
  return _prim == NULL;
}

template <typename T>
T deque<T>::front() const {
  return _prim->info;
}

template <typename T>
T deque<T>::rear() const {
  return _prim->ant->info;
}

template<typename T>
void deque<T>::push(T e) {
    node* nn = new node;
    try {
        nn->info = e;
    }catch(...) {
        delete nn;
        throw;
    }
    if(_long == 0){
        nn->seg = nn;
        nn->ant = nn;
        _prim = nn;
    } else{
        nn->seg = _prim;
        nn->ant = _prim->ant;
        _prim->ant = nn;
        nn->ant->seg = nn;
        _prim = nn;
    }
    _long++;
}

template<typename T>
void deque<T>::inject(T e) {
    node* nn = new node;
    try {
        nn->info = e;
    }catch(...) {
        delete nn;
        throw;
    }
    if(_long == 0){
        nn->seg = nn;
        nn->ant = nn;
        _prim = nn;
    } else{
        nn->ant = _prim->ant;
        nn->seg = _prim;
        _prim -> ant = nn;
        nn -> ant -> seg = nn;
    }
    _long++;
}

template<typename T>
void deque<T>::pop() {
    if(_long > 1){
        node *n = _prim;
        _prim = n->seg;
        _prim->ant = n->ant;
        n->ant->seg = _prim;
        delete n;
        _long--;
    } else if(_long == 1){
        node *n = _prim;
        _prim = NULL;
        delete n;
        _long--;
    }
}

template<typename T>
void deque<T>::eject() {
    if(_long > 1){
        node *n = _prim->ant;
        _prim->ant = n->ant;
        n->ant->seg = _prim;
        delete n;
        _long--;
    } else if(_long == 1){
        node *n = _prim;
        _prim = NULL;
        delete n;
        _long--;
    }
}

template <typename T>
void mostra(deque<T> dq) {
// Pre: True
// Post: Mostra els elements de dq pel cout entre claudàtors i separats per espais.
  cout << "[";
  if (not dq.empty()) {
    cout << dq.front();
    dq.pop();
  }
  while (not dq.empty()) {
    cout << " " << dq.front();
    dq.pop();
  }
  cout << "]";
}

template <typename T>
void mostra_invertida(deque<T> dq) {
// Pre: True
// Post: Mostra en ordre invers els elements de dq pel cout entre claudàtors i separats per espais.
  cout << "[";
  if (not dq.empty()) {
    cout << dq.rear();
    dq.eject();
  }
  while (not dq.empty()) {
    cout << " " << dq.rear();
    dq.eject();
  }
  cout << "]";
}




int main() {
  string linea, comanda;
  int n;
  deque<int> dq;

  // Processem comandes
  while (getline(cin, linea)) {
    cout << linea << ": ";
    istringstream ss(linea);
    ss >> comanda;

    if (comanda == "size") {
      cout << dq.size();

    } else if (comanda == "empty") {
      cout << boolalpha << dq.empty();

    } else if (comanda == "front") {
      cout << dq.front();

    } else if (comanda == "rear") {
      cout << dq.rear();

    } else if (comanda == "push") {
      ss >> n;
      cout << n;
      dq.push(n);

    } else if (comanda == "inject") {
      ss >> n;
      cout << n;
      dq.inject(n);

    } else if (comanda == "pop") {
      cout << dq.front();
      dq.pop();

    } else if (comanda == "eject") {
      cout << dq.rear();
      dq.eject();

    } else if (comanda == "mostra") {
      mostra(dq);

    } else if (comanda == "mostra_invertida") {
      mostra_invertida(dq);
    }
    cout<<endl;
  }
  return 0;
}
