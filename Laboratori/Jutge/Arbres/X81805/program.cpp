#include "arbreBin.hpp"

using namespace std;

arbreBin<int> sum_abin(arbreBin<int> a){
  arbreBin<int> b, ae, ad;
  int arr = 0;

  if(a.fe().es_buit() && a.fd().es_buit()) b = a;
  else{
    if(not a.fe().es_buit() && a.fd().es_buit()){
      ae = sum_abin(a.fe());
      arr = a.arrel() + ae.arrel();
    }
    else if(a.fe().es_buit() && not a.fd().es_buit()){
      ad = sum_abin(a.fd());
      arr = a.arrel() + ad.arrel();;
    }
    else{
      ae = sum_abin(a.fe());
      ad = sum_abin(a.fd());
      if(not ae.es_buit() && not ad.es_buit()){
        arr = a.arrel() + ae.arrel();
        arr = arr + ad.arrel();
      }
      else if(not ae.es_buit() && ad.es_buit()) arr = a.arrel() + ae.arrel();
      else if(ae.es_buit() && not ad.es_buit()) arr = a.arrel() + ad.arrel();
    }
    arbreBin<int> aux(arr, ae, ad);
    b = aux;
  }
  return b;
}

int main() {
  arbreBin<int> ara, arb;
  cin >> ara;
  if(not ara.es_buit()) arb = sum_abin(ara);
  cout << arb << endl;
}
