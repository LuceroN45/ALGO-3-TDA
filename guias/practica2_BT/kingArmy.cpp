#include <iostream>
#include <vector>
#include <algorithm> // Requerido para std::max

using namespace std;
const int NegINF = -1e9;
const int INF = 1e9;
const int INDEF = -1;
/*
  El rey Cambyses está interesado en armar ejércitos en una serie de días consecutivos. Mas aun, le interesa que el número de personas de su ejército en el dia di sea equivalente a la suma del número de personas del ejército que formó el dia i − 1 e i − 2. La excepción para esto es en el día 0 y 1, en cuyo caso la cantidad de personas en esos días va a ser siempre 1. Para el es muy complicado determinar este número, entonces nos pidió que lo ayudemos. Dado un dia N, tenemos que devolver el número de personas de su ejército.
  Pensar un algoritmo O(N) para resolver este problema y demostrar su correctitud y complejidad.
*/

// recursion O(2**n) temporal 
// int solve(int n) {
//   if(n <= 1){
//     return 1;
//   }

//   return solve(n - 1) + solve(n - 2); 
// }

//Optimizacion con memorizacion ej 22
vector<int> pd;
int solve(int n) {
  if(pd[n] != INDEF){
    return pd[n];
  }

  if(n <= 1){
    pd[n] = 1;
    return pd[n];
  }

  pd[n] = solve(n - 1) + solve(n - 2); 

  return pd[n];
}


int main(int argc, char const *argv[])
{
  int n;
  n = 10;
  // n = 9;
  //TOP DOWN O(n) espacial y temporal
  // cout << "Ingrese que dia mi rey: ";
  // cin >> n;

  // pd.resize(n, INDEF);
  // int res = solve(n);
  // cout << "Su ejercito debe ser de " << n << "soldados mi rey";

  //BOTTOM UP O(n) temporal O(1) espacial //Ejercio 22

  int prev = 0;
  int anterior = 1;
  int actual = 1;
  for(int i = 2; i <= n; i++){
    prev = anterior;
    anterior = actual;
    actual = anterior + prev;
  }
  cout << "Debe usar " << actual << " soldados senor";

  /* code */
  return 0;
}
