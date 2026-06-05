#include <iostream>
#include <vector>
#include <algorithm> // Requerido para std::max
// #define fore(a,b,c) = for(int a = b; a<c; a++)

using namespace std;
const int NegINF = -1e9;
const int INF = 1e9;
const int INDEF = -1;

/*
Debemos cortar una vara de madera en varios lugares predeterminados. Sabemos que el costo de realizar un corte en una madera de longitud ℓ es ℓ (y luego de realizar ese corte quedarán 2 varas de longitudes que sumarán ℓ).
Por ejemplo, si tenemos una vara de longitud 10 metros que debe ser cortada a los 2, 4 y 7 metros desde un extremo, entonces los cortes se pueden realizar, entreotras maneras, de las siguientes formas:
  Primero cortar en la posición 2, después en la 4 y después en la 7. Esta resulta en un costo de 10 + 8 + 6 = 24 porque el primer corte se hizo en una vara de longitud 10 metros, el segundo en una de 8 metros y el último en una de 6 metros.
  Cortar primero donde dice 4, después donde dice 2, y finalmente donde dice 7, con un costo de 10 + 4 + 6 = 20, que es menor.
Queremos encontrar el mínimo costo p osible de cortar una vara de longitud ℓ.
*/

/* Supongo poder acceder siempre a c
costo(i,j) = j - i + min{c <- C / i < c < j}( costo(i,c) + costo(c,j) );
*/

vector<vector<int>> MEMO;
vector<int> cortes;

// solve Top Down con lista de cortes sin 0 y l
//  int solve(int i, int j)
//  {
//    if(MEMO[i][j] != INDEF){
//      return MEMO[i][j];
//    }
//    if (i == j)
//    {
//      return 0;
//    }

//   bool isCutted = false;
//   int res = INF;
//   for(int c : cortes){
//     if(i < c && c < j){
//       isCutted = true;
//       res = min(res,j - i + solve(i,c) + solve(c,j));
//     }
//   }

//   //No hubo cortes que hacer
//   if(!isCutted){
//     MEMO[i][j] = 0;
//     return MEMO[i][j];
//   }

//   MEMO[i][j] = res;
//   return MEMO[i][j];
// }

/*

Supongamos que se ordenan los elementos de C en un vector cortes y se agrega un 0 al principio y un ℓ al final.
Luego, se considera que el mínimo costo para cortar desde el i-ésimo punto de corte en cortes hasta el j-ésimo punto de corte será el resultado buscado si i = 1
y j = |C|+ 2.

costo(i,j) = j - i min{c <- C : i < c < j}(costo(i,c) + costo(c,j))

f(i,j) = | i == j - 1 -> 0
         |
*/
int solve(int i, int j)
{
  if (MEMO[i][j] != INDEF)
  {
    return MEMO[i][j];
  }
  if (i == j)
  {
    return 0;
  }

  int res = INF;
  for (int k = i + 1; k < j; k++)
  {
    res = min(res, cortes[j] - cortes[i] + solve(i, k) + solve(k, j));
  }

  if (res == INF)
  {
    MEMO[i][j] = 0;
    return MEMO[i][j];
  }

  MEMO[i][j] = res;
  return MEMO[i][j];
}

int main(int argc, char const *argv[])
{
  // pruebas
  int l = 10;
  int C = 3;
  // cortes = {2, 4, 7};
  cortes = {0, 2, 4, 7, 10};
  
  // TOP DOWN
  // int l;
  // int C;


  // cout << "Ingrese el largo de la madera a cortar: ";
  // cin >> l;
  // MEMO.resize(l + 2, vector<int>(l + 2, INDEF));

  // cout << "Indique la cantidad de cortes a realizar: ";
  // cin >> C;
  // cortes.resize(C + 2);
  // cortes[0] = 0;
  // cortes[cortes.size() - 1] = l;
  // cout << "Los cortes: ";
  // for (int i = 1; i < cortes.size() - 1; i++)
  // {
  //   cin >> cortes[i];
  // }

  // sort(cortes.begin(), cortes.end());
  // int res = solve(0, C + 1);
  // cout << "El resultado es: " << res << endl;

  // BOTTOM UP
  // Quiero resolver una instancia de largo j - i.
  // necesito saber el costo de las instancias menoras
  // Mis caso base son j == i -> 0
  //INICIALIZO LA MATRIZ DE TAMANO C+2 osea cantidad de cortes + 2. Incio + longitud de la madera
  MEMO.resize(C+2,vector<int>(C+2,INDEF));

  //Para resolver una instancia de largo 0 es un CB es 0
  //Para resolver una instacia de largo l, tengo que haber resolvido todas las de largo menor
  for(int gap = 0; gap < C+2; gap++){

    // j es el incio de mi corte. Recorro desde 0 hasta donde pueda con mi largo actual
    for(int j = 0; j + gap < C+2; j++){

      //El final de mi corte es donde arranque mas el largo
      int fin = j + gap;

      int minimo = INF;

      //Busco el minimo k entre el inicio, j, y el final
      for(int k = j + 1; k < fin; k++){
        int costo = (cortes[fin] - cortes[j]) + MEMO[j][k] + MEMO[k][fin];
        minimo = min(minimo, costo);
      }

      // Si es un caso base no entra en el for anterior por lo tanto es cero
      if(minimo == INF){
        MEMO[j][fin] = 0;
      } else {
        MEMO[j][fin] = minimo;
      }
    }
  }

  //mi respuesta es el costo minimo de cortar una madera en la posicion 0 hasta l, guardado en C + 1
  cout << "El resultado es: " << MEMO[0][C + 1] << endl;

  return 0;
}
