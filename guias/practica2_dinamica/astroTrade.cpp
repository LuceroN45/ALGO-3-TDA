#include <iostream>
#include <vector>
#include <algorithm> // Requerido para std::max

using namespace std;
vector<int> precios;
vector<vector<int>> dias;
const int NegINF = -1e9;
const int INDEF = -1;

/*
MaximaGananciaNeta(c,j) // Maxima ganancia Neta con c asteroides el dia al fin del dia j
  -INF si c < 0 o c > j
  Maximo{mgn(c-1,j-1) - p[j], mgn(c+1,j-1) + p[j], mgn(c,j-1)} Sino //i.e, maximo entre comprar en j, vender en j o no hacer nada en j

 Casos Base
 si j =0 0 => 0 //porque no tiene asteroides el dia 0

 Respuesta:
 mgn(0,n) //donde n es la cant de dias. La sol optima termina con 0 asteroides el dia n
*/

int solveTopDown(int c, int j)
{
  //Si tengo mas asteroides que dias no puedo venderlos todos
  if(c < 0 || c > precios.size() - j - 1){
    return NegINF;
  }

  //El primer dia arranca con 0 asteroides y por lo tanto cero ganancia
  if(j < 0){
    if(c==0){
      return 0;
    } else {
      return NegINF;
    }
  }

  // Ya lo calcule entonces lo leo
  if(dias[c][j] != INDEF){
    return dias[c][j];
  }

  //ayer no hice nada
  int res = solveTopDown(c,j-1);

  //ayer tenia uno mas y hoy lo vendi
  res = max(res,solveTopDown(c+1,j-1) + precios[j]);
  //ayer tenia uno menos y hoy compre
  res = max(res,solveTopDown(c-1,j-1) - precios[j]);
  dias[c][j] = res;

  return dias[c][j];
}

//Solve Bottom-Up
int solveBottomUp(int n) // La maxima ganancia neta del dia i
{
  // vector<vector<int>> MEMO = vector<vector<int>>(n+1,vector<int>(n+1,NegINF)); //Dinamica Bottom-Up sin mejora en memoria
  vector<vector<int>> MEMO = vector<vector<int>>(2,vector<int>(n+1,NegINF)); //Memoria O(2N)=O(N)
  int HOY;
  int AYER;

  MEMO[0][0] = 0; //El dia 0 comienzo con 0 asteroides y 0 ganancia

  //Tomo todos los dias
  for(int d = 1; d <= n; d++){
    //Solo guardo los valores de ayer y hoy
    AYER = (d-1) % 2;
    HOY = d % 2;

    for(int a = 0; a <= n; a++){
      int res = MEMO[AYER][a];

      //NO ENTRA CUANDO: tengo asteroides negativos
      if(a > 0){
        res = max(res,MEMO[AYER][a-1] - precios[d-1]);
      }

      //NO ENTRA CUANDO: tengo mas asteroides que dias
      if(a < precios.size()){
        res = max(res,MEMO[AYER][a+1] + precios[d-1]);
      }
      MEMO[HOY][a] = res;
    }
  }

  return MEMO[HOY][0];
}

int main(int argc, char const *argv[])
{
  // precios = {3,2,5,6};
  precios = {3,6,10};
  int n = precios.size();

  // Dinamica Top-Down
  // dias.resize(n + 1,vector<int>(n + 1,INDEF));
  // cout << solveTopDown(0,n-1) << endl;

  cout << solveBottomUp(n) << endl;
}
