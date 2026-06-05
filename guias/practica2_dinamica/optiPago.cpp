#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e9;

vector<vector<pair<int,int>>> memoria;

// algoritmo recursivo: 
  // CC(B,c) = {
  //     SI |B|=0 & c > 0 entonces (inf,inf) 
  //     SI |B|=0 & c <= 0 entonces (0,0)
  //     Sino min{cc(B-ultimo,c),(cc(B-ultimo,c-ultimo).first + ultimo,cc(B-ultimo,c-ultimo).second+1)}
  // }
// Donde ultimo es el ultimo elemento de B, suponer que B esta ordenado y min compara como pide el enunciado.

pair<int,int> compararTupla(pair<int,int> a, pair<int,int> b){ //O(1) son solo comparaciones de menor igual.
  if(a.first < b.first){
    return a;

  } else if(a.first > b.first){
    return b;
    
  } else {
    if(a.second < b.second){
      return a;
    } else {
      return b;
    }
  }
}

pair<int,int> solve(vector<int> &Billetes, int costo, int i){
  // Casos base                                       //O(1)
  if (costo <= 0) {
    return {0,0};
  }
  if (i < 0) {
    if (costo <= 0) {
      return {0,0};
    } else {
      return {INF,INF};
    }
  }

  //Chequeamos si ya calculamos ese estado.

  if(memoria[i][costo] != make_pair(-1,-1)){
    return memoria[i][costo];
  }

  int ultimo = Billetes[i];           //O(1) es lectura de memoria
  
  pair<int,int> pair1 = solve(Billetes,costo,i-1);            //O(solve(n-1))
  pair<int,int> b = solve(Billetes,costo-ultimo,i-1);     //O(solve(n-1))
  pair<int,int> pair2;

  if (b.first == INF) { //Evito overflow
    pair2 = {INF, INF};
  } else {
    pair2 = make_pair(b.first + ultimo, b.second + 1); //O(1)
  }
  
  pair<int,int> sol = compararTupla(pair1, pair2);         //O(1)

  memoria[i][costo] = sol;

  return memoria[i][costo]; 
  //final sin dinamica T(n) = 2T(n-1) + O(1) = O(2**n)
  // con dinámica: O(n*c)  <- hay n*c estados, cada uno O(1)

  // #estados = (cantidad de billetes)*(cantidad de posibles costos) = n*c = O(nc)
  // cantidad de llamados recursivos, simepre hago 2 llamados osea = O(2**n)
  // Hay superposicion cuando c < (2**n)/n
}

int main(int argc, char const *argv[])
{
  // vector<int> B = {2,3,5,10,20,20};
  // vector<int> B = {3,5,9};
  // vector<int> B = {4,7,10};
  vector<int> B ={1,2,5,7,10,13,15,20,25,30,50,100};
  // B={1,2,5,7,10,13,15,20,25,30,50,100}, c=137
  // int c = 14;
  // int c = 7;
  // int c = 11;
  int c = 137;
  // B={3,5,9}, c=7
  // B={4,7,10}, c=11

  for(int i = 0; i < B.size(); i++){
    memoria.push_back({});
    for(int j = 0; j <= c; j++){
      memoria[i].push_back({-1,-1});
    }
  }

  pair<int,int> sol = solve(B,c,B.size()-1);


  cout << sol.first << endl;
  cout <<  sol.second << endl;
  return 0;
}
