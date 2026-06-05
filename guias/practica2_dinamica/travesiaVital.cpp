#include <iostream>
#include <vector>
#include <algorithm> // Requerido para std::max

using namespace std;
const int NegINF = -1e9;
const int INF = 1e9;
const int INDEF = -1;

/*

Mi funcion f(i,j) = costo minimo de vida necesario para llegar a i j.

caso base i = 0, j = 0. El costo es igual a 1 + Aij
si es negativo el costo es 1 |A_ij|
si es positivo el costo es 1

caso inductivo i j. El costo de llegar a i j es
el minimo entre el costo de llegar i-1 j y i j-1 
*/

vector<vector<int>> campo = {};
bool bt(int i, int j, int vida){
  //Caso base invalido
  if(vida + campo[i][j] < 1){
    //con esa vida no paso esta casilla
    return false;
  }

  //Caso base final
  if(i == campo.size() - 1 && j == campo[0].size() - 1){
    //devuelvo si es valido o no
    return vida + campo[i][j] >= 1;
  }

  if(i == campo.size() - 1 && j != campo[0].size() - 1){
    //Si estoy abajo del todo
    return bt(i,j+1, vida + campo[i][j]);
  } else if (i != campo.size() - 1 && j == campo[0].size() - 1){
    //Si estoy a la derecha del todo
    return bt(i+1,j, vida + campo[i][j]);
  }

  //sino
  return bt(i+1,j,vida + campo[i][j]) || bt(i,j+1, vida + campo[i][j]);
  /*
  El costo depende de la cota de la vida.
  Esta funcion se que termina, a pesar del bucle que la llama ya que puedo tomar un camino cualquiera que me lleve de 0,0 a m,n y calcular la suma de modulos, al ser enteros esa suma es finita entonces, con esa cantidad de vida se que cruzo el campo.

  la cantidad de nodos es 2 a la m + n ya que recorro toda la matriz, y nunca vuelvo atras. En cada iteracion tengo dos llamados recursivos

  cota_vida * 2^(m+n)
  Donde cota_vida es la suma de módulos del camino más caro.
  */
}

/*
la mínima vida necesaria al llegar a la posición i,j es el resultado de restar al mínimo entre la mínima vida necesaria en i + 1,j y aquella en i,j + 1, el valor Ai,j, salvo que eso fuera menor o igual que 0, en cuyo caso sería 1.

tomando la definicion de minima vida necesaria del ejercicio.

pd_tp(i,j) = la minima vida necesaria al llegar a i j.

pd_tp(i,j) = | i == m && j == n -> 1
             | i == m && j != n -> max(1, pd-tp(i,j+1) - A_ij) //Abajo del todo
             | i != m && j == n -> max(1, pd-tp(i+1,j) - A_ij) //derecha del todo
             | sino             -> max(1, min(pd-tp(i,j+1),pd-tp(i+1,j)) - A_ij) //funcion dada
*/
vector<vector<int>> MEMO;
int pd_tp(int i, int j){
  if(MEMO[i][j] != INDEF){
    return MEMO[i][j];
  }


  if(i == campo.size() - 1 && j == campo[0].size() - 1){
    MEMO[i][j] = max(1, 1 - campo[i][j]); 
    return MEMO[i][j];
  }


  if(i == campo.size() - 1 && j != campo[0].size() - 1){
    MEMO[i][j] = max(1, pd_tp(i,j+1) - campo[i][j]);
    return MEMO[i][j];
  }
  if(i != campo.size() - 1 && j == campo[0].size() - 1){
    MEMO[i][j] = max(1, pd_tp(i+1,j) - campo[i][j]);
    return MEMO[i][j];
  }

  int minimo = min(pd_tp(i+1,j), pd_tp(i,j+1));

  MEMO[i][j] = max(1, minimo - campo[i][j]);
  return MEMO[i][j];

  //costo temporal y espacial M*N que es la cantidad de estados posibles.
}


int main(int argc, char const *argv[])
{


  //  CODIGO BT
  // int m;
  // cout << "cantidad de filas: ";
  // cin >> m;
  // int n;
  // cout << "cantidad de columnas: ";
  // cin >> n;
  // MEMO.resize(m,vector<int>(n,INDEF));

  // campo.resize(m, vector<int>(n,INDEF));

  // for(int i = 0; i < m; i++){
  //   cout << "fila " << i << ":";
  //   for (int j = 0; j < n; j++){
  //     cin >> campo[i][j];
  //   }
  // }

  // campo = {{-2,-3,3},{-5,-10,1},{10,30,-5}};
  // campo = {{-1,5,-3},{2,-8,1},{-4,3,-2}};
  campo = {{-2,3,-1,4},
               {1,-5,2,-3},
               {-4,2,1,-2}};
  int m = campo.size(); 
  int n = campo[0].size();
  MEMO.resize(m,vector<int>(n,INDEF));

  //Veo la primera vida que cumple
  // int vida_min = 0;
  // bool encontrado = false;
  // while(!encontrado){
  //   vida_min ++;
  //   encontrado = bt(0,0,vida_min);
  // }

  // cout << "el resultado es " << vida_min << endl;
  
  //PD TOP DOWN
  // int res = pd_tp(0,0);
  // cout << "El resultado es: " << MEMO[0][0] << endl;
  // cout << "El resultado es: " << res << endl;
  
  //PD BOTTOM UP
  // Sin mejora espacial
  // MEMO[m-1][n-1] = max(1, 1 - campo[m-1][n-1]);
  
  // for(int j = n - 2; j >= 0; j--){
  //   MEMO[m - 1][j] = max(1, MEMO[m - 1][j + 1] - campo[m - 1][j]); 
  // }
  // for(int i = m - 2; i >= 0; i--){
  //   MEMO[i][n - 1] = max(1, MEMO[i + 1][n - 1] - campo[i][n - 1]); 
  // }
  
  // for(int i = m - 2; i >= 0; i--){
  //   for(int j = n - 2; j >= 0; j--){
  //     MEMO[i][j] = max(1, min(MEMO[i+1][j],MEMO[i][j+1]) - campo[i][j]);
  //   }
  // }
  // cout << "El resultado es: " << MEMO[0][0] << endl;
  
  //mejora espacial O(min(m,n))
  vector<int> pd;

  if(n < m){
    pd.resize(n,INDEF);
    for(int i = m - 1; i >= 0; i--){
      for(int j = n - 1; j >= 0; j--){
        if(i == m - 1 && j == n - 1){
          pd[j] = max(1, 1 - campo[m-1][n-1]);
        } else if (i == m - 1 && j != n - 1) {
          pd[j] = max(1, pd[j + 1] - campo[i][j]);
        } else if (i != m - 1 && j == n - 1) {
          pd[j] = max(1, pd[j] - campo[i][j]);
        } else {
          pd[j] = max(1, min(pd[j],pd[j + 1]) - campo[i][j]);
        }
      }
    }
  } else {
    pd.resize(m,INDEF);
    for(int j = n - 1; j >= 0; j--){
      for(int i = m - 1; i >= 0; i--){
        if(i == m - 1 && j == n - 1){
          pd[i] = max(1, 1 - campo[m-1][n-1]);
        } else if (i == m - 1 && j != n - 1) {
          pd[i] = max(1, pd[i] - campo[i][j]);
        } else if (i != m - 1 && j == n - 1) {
          pd[i] = max(1, pd[i + 1] - campo[i][j]);
        } else {
          pd[i] = max(1, min(pd[i],pd[i + 1]) - campo[i][j]);
        }
      }
    }
  }
  cout << "El resultado es: " << pd[0] << endl;

  return 0;
}
