#include <iostream>
#include <vector>

using namespace std;

int SumaSubSet(vector<vector<int>> &Matriz, vector<int> &subConjunto)
{
  int suma = 0;

  for(int i: subConjunto) // O(n**2/2) = O(n**2)
  {
    for(int j = 0; j <= i; j++)
    {
      suma += Matriz[i][j];
    }
  }

  return suma;
}

void solve(vector<vector<int>> &Matriz, int K, int i,vector<int> &solParcial, int &maximo, vector<int> &mejorSol)
{
  if (i==Matriz.size()){//Termine de recorrer todas las opciones, no quedan mas para elegir, termino la recursion
    return;
  }
  // k=longitud objetivo
  // Matriz.size()-i+1= Cantidad de opciones restantes, tomo la longitud total - el iterador
  //Si la longitud, es mas grande que las opciones elegidas + las posibles restantes, termina.
  //Ej: sol={1} opcionesRestantes={2,3} k=4, 4 > 1+2. 
  if(K > solParcial.size() + (Matriz.size()-i+1)){
    return;
  }
  int sumatoria;


  if (solParcial.size() == K){
    sumatoria = SumaSubSet(Matriz,solParcial);
    if (maximo < sumatoria){
      maximo = sumatoria;
      mejorSol = solParcial;
    }
  }


  solParcial.push_back(i);
  solve(Matriz,K,i+1,solParcial,maximo,mejorSol);
  solParcial.pop_back();
  solve(Matriz,K,i+1,solParcial,maximo,mejorSol);

  //Peor caso: O(2**n) por la cantidad de subconjuntos posibles, y O(n**2) por la suma de cada subconjunto, entonces O(2**n * n**2)
}


int main(int argc, char const *argv[])
{
  vector<vector<int>> D = {
      {0 , 10, 10, 1},
      {10, 0 , 5 , 2},
      {10, 5 , 0 , 1},
      {1 , 2 , 1 , 0}};

  vector<int> SolParcial = {};
  vector<int> mejorSol = {};
  int maximo = -1;

  solve(D,3,0, SolParcial,maximo,mejorSol);


  cout << maximo*2 << endl;
  for (int x : mejorSol) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}


