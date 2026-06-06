#include <iostream>
#include <vector>
#include <algorithm> // Requerido para std::max

using namespace std;
const int NegINF = -1e9;
const int INF = 1e9;
const int INDEF = -1;

/*
Tomas tiene N días de vacaciones, donde puede hacer actividades:
Se pueden hacer 2 actividades: gimnasio y competencias. Cada día puede tener disponible ninguna, alguna o ambas.
Tomas cada dia puede hacer una actividad que este disponible, siempre que no la haya hecho el día anterior o descansar.
Tomas quiere minimizar los días de descanso.
  a) Diseñar un algoritmo O(N) que calcule la mínima cantidad de días de descanso.
  b) Probar la correctitud y complejidad del algoritmo.
  c) Indicar cómo se puede reconstruir la solución. Es decir, indicarle a Tomas qué hara cada día.

Ayuda: Consideren el siguiente ejemplo:
  N = 4
  Días con gimnasio disponible: 2, 3
  Días con competencias disponibles: 1, 2
Puede lograr tener solo 2 días de descanso.

pd: que rompe bolas tomas que duerma los n dias
*/

const int D = 0; //descansar
const int C = 1; //competir
const int G = 2; //Gimnasio

vector<vector<int>> actividades;
vector<vector<int>> pd;

int puede_competir(int d, int a){
  if(a == C){
    return 0;
  }

  return actividades[d][C];
}

int puede_gimnasio(int d, int a){
  if(a == G){
    return 0;
  }

  return actividades[d][G];
}

int solve_BT(int d, int a){
  if(d == actividades.size()){
    return 0;
  }

  int res = 1 + solve_BT(d+1,D);

  if(puede_competir(d,a)){
    res = min(res,solve_BT(d+1,C));
  }
  if(puede_gimnasio(d,a)){
    res = min(res,solve_BT(d+1,G));
  }

  return res;
}

int solve_pd(int d,int a){
  if(d == actividades.size()){
    return 0;
  }

  if(pd[d][a] != INDEF){
    return pd[d][a];
  }

  pd[d][a] = 1 + solve_pd(d+1,D);

  if(puede_competir(d,a)){
    pd[d][a] = min(pd[d][a],solve_pd(d+1,C));
  }
  if(puede_gimnasio(d,a)){
    pd[d][a] = min(pd[d][a],solve_pd(d+1,G));
  }

  return pd[d][a];

}

int main(int argc, char const *argv[])
{
//   N=4
// // Días con gimnasio disponible: 0, 1, 2, 3 (todos)
// // Días con competencias disponibles: 0 (solo el primero)
  int d = 3;
  actividades.resize(d,vector<int>(3,0));
  vector<int> dias_gim = {1,0,0,0};
  vector<int> dias_comp = {0,0,0,1};

  for(int i = 0; i < d; i++){
    actividades[i][G] = dias_gim[i];
    actividades[i][C] = dias_comp[i];
  }

  // pd.resize(d,vector<int>(3,INDEF));

  // int res = solve_BT(0,D);
  // int res = solve_pd(0,D);
  // cout << res;


  // BOTTOM UP //optimizacon espacial O(1) ej 22
  // para resolver una instacia solo necesito saber los casos con las 3 actividades del dia siguiente
  vector<vector<int>> MEMO;
  
  //Inicializamos las variables complejidad espacial O(1)

  //MEMO solo guardo las actividades de HOY y las de MANANA
  MEMO.resize(2,vector<int>(3,INDEF));

  // Inicializo HOY como el ultimo dia y manana no hay
  int hoy = d % 2;
  int manana; //no tengo enie perdon, igual re raro codear con n

  //CASO BASE
  MEMO[hoy][D] = 0; //como arrancamos en el dia D y vamos para atras, no hay actividades para hacer
  MEMO[hoy][G] = 0;
  MEMO[hoy][C] = 0;

  //Voy desde el dia d-1 hasta 0 
  for(int i = d - 1; i >= 0; i--){
    // actualizo las variables
    manana = hoy;
    hoy = i % 2;
    
    //como hoy descanso sumo simpre mas el minimo posible manana
    MEMO[hoy][D] = 1 + min(MEMO[manana][D],min(MEMO[manana][G],MEMO[manana][C]));
    
    //Veo si en el dia i puede competir
    if(actividades[i][C]){

      //Si puede competir entonces el minimo posible hoy es o descansa manana o ir al gim. No puede competir
      MEMO[hoy][C] = min(MEMO[manana][D],MEMO[manana][G]);
    } else {

      //Si no puede competir hoy entonces es inf ya que no puede elegirse nunca
      MEMO[hoy][C] = INF;
    }

    //Idem para gimnasio
    if(actividades[i][G]){
      MEMO[hoy][G] = min(MEMO[manana][D],MEMO[manana][C]);
    } else {
      MEMO[hoy][G] = INF;
    }
  }

  //La respuesta es el minimo de ver con que arranco
  int r = min(MEMO[hoy][C],min(MEMO[hoy][G],MEMO[hoy][D]));
  cout << "deberia ser 2: " << r;


  /* code */
  return 0;
}
