#include "arbreBin.hpp"

using namespace std;

bool sumFills_i(arbreBin<int> a){
  bool sf = true;
  if(not a.fe().es_buit() && not a.fd().es_buit()){
    if((a.fe().arrel() + a.fd().arrel()) == a.arrel()) {
      sf = (sumFills_i(a.fe()) && sumFills_i(a.fd()));
    }
    else sf = false;
  }
  else if(not a.fe().es_buit() && a.fd().es_buit()){
    if((a.fe().arrel() + 0) == a.arrel()) {
      sf = sumFills_i(a.fe());
    }
    else sf = false;
  }
  else if(a.fe().es_buit() && not a.fd().es_buit()){
    if((0 + a.fd().arrel()) == a.arrel()) {
      sf = sumFills_i(a.fd());
    }
    else sf = false;
  }
  return sf;
}

void sumFills(arbreBin<int> a){
  if (sumFills_i(a)) cout << "L'arbre compleix la propietat 'Suma dels fills'." << endl;
  else cout << "L'arbre no compleix la propietat 'Suma dels fills'." << endl;
}

int main() {
  arbreBin<int> ar;
  cin >> ar;
  cout << ar << endl;
  if(not ar.es_buit()) sumFills(ar);
  else cout << "L'arbre compleix la propietat 'Suma dels fills'." << endl;
}
