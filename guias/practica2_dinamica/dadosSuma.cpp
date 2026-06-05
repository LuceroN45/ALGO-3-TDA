#include <iostream>
#include <vector>
#include <algorithm> // Requerido para std::max

using namespace std;
const int NegINF = -1e9;
const int INF = 1e9;
const int INDEF = -1;

int k;
vector<vector<int>> MEMO;
int bt_A(int n, int s){
  if(n == 0){
    return s == 0 ? 1 : 0;
  }

  if(n >= 1 && s <= 0){
    return 0;
  }

  int res = 0;
  for(int i = 1; i <= k; i++){
    res = res + bt_A(n-1,s-i);
  }

  return res;
}

int bt_B(int n, int s, int k){
  if(n== 0){
    return s == 0 ? 1 : 0;
  }
  
  //Poda por optimizacion: (n*k < s) n*k es el numero mas grade que puedo formar con n dados de k caras. Si ese numero es mas chico que la suma total entonces no puedo nunca formarlo
  if((n >= 1 && s <= 0) || (n*k < s)){
    return 0;
  }

  int res = 0;
  for(int i = 1; i <= k; i++){
    res = res + bt_B(n-1, s-i, i);
  }

  return res;
}

int pd_tp_A(int n, int s){
  //No tiene sentido memorizarlo. En un mismo nivel osea mismo N no se repiten los s.
  if(s < 0){
    return 0;
  }
  
  if(MEMO[n][s] != INDEF){
    return MEMO[n][s];
  }

  if(n == 0){
    MEMO[n][s] = s == 0 ? 1 : 0;
    return MEMO[n][s];
  }
  
  if(n >= 1 && s == 0){
    MEMO[n][s] = 0;
    return MEMO[n][s];
  }

  int res = 0;
  for(int i = 1; i <= k; i++){
    res = res + bt_A(n-1,s-i);
  }

  MEMO[n][s] = res;
  return MEMO[n][s];
}

vector<vector<vector<int>>> pd;
int pd_tp_B(int n, int s, int k){
  if(s < 0){
    return 0;
  }

  if(pd[n][s][k] != INDEF){
    return pd[n][s][k];
  }

  if(k == 0){
    pd[n][s][k] = (s == 0 && n == 0) ? 1 : 0; 
    return pd[n][s][k];
  }

  if(n == 0){
    pd[n][s][k] = s == 0 ? 1 : 0; 
    return pd[n][s][k];
  }
  
  //Poda por optimizacion: (n*k < s) n*k es el numero mas grade que puedo formar con n dados de k caras. Si ese numero es mas chico que la suma total entonces no puedo nunca formarlo
  if((n >= 1 && s <= 0) || (n*k < s)){
    pd[n][s][k] = 0;
    return pd[n][s][k];
  }

  int res = bt_B(n,s,k-1) + bt_B(n-1,s-k,k);

  pd[n][s][k] = res;
  return pd[n][s][k];
}

int main(int argc, char const *argv[])
{
  //prueba
  k = 4;
  int n = 3;
  int s = 6;
  
  // k = 6;
  // int n = 3;
  // int s = 13;
  
  // int r = bt_A(n,s);
  // cout << "El res CASO A es: " << r << endl;
  
  // r = bt_B(n,s,k);
  // cout << "El res CASO B es: " << r << endl;
  
  // El árbol de recursión tiene k^n hojas, pero solo hay n·s estados distintos. Como k^n crece mucho más rápido que n·s, muchos estados deben repetirse. Por lo tanto f goza de la propiedad de superposición de subproblemas.
  
  // El árbol de recursión tiene k^n hojas, pero solo hay n·s·k estados distintos. Como k^n crece mucho más rápido que n·s, muchos estados deben repetirse. Por lo tanto g goza de la propiedad de superposición de subproblemas.
  
  // TOP DOWN CASO A f(n,s)
  MEMO.resize(n+1,vector<int>(s+1,INDEF));
  int r_A = pd_tp_A(n,s);
  cout << "El res CASO A con memo es: " << r_A << endl;
  
  pd.resize(n+1, vector<vector<int>>(s+1, vector<int>(k+1, INDEF)));
  int r_B = pd_tp_B(n,s,k);
  cout << "El res CASO B con memo es: " << r_B << endl;


  
  return 0;
}
