#include <iostream>
#include <vector>
#include <algorithm> // Requerido para std::max

using namespace std;
const int NegINF = -1e9;
const int INF = 1e9;
const int INDEF = -1;

vector<int> TIEMPO_SALVAR;
vector<int> TIEMPO_UTIL;
vector<int> VALOR;
struct fire
{
  int t; // Costo de salvar
  int d; // Tiempo de vida
  int p; // Precio
};
vector<fire> articulos;
vector<vector<int>> MEMO;


/*
El sabueso de preguntas está en problemas. Su casa se incendia!. Es tiempo de salvar los artículos más valiosos. 
Cada artículo tiene los parámetros:
  El tiempo t entero que estima el sabueso que le tomara salvarlo.
  El tiempo d entero que estima el sabueso a partir del cuál se quema el articulo y no sirve
  más (inclusive si lo está rescatando en ese momento)
  El valor p del artículo para el sabueso.
El sabueso queire maximizar la suma de los valores de los artículos que puede salvar, considerando
que:
  Salva un árticulo luego de otro, uno a la vez.
  Si un artículo A le toma ta segundos y luego salva el B, entonces le habrá tomado tA + tB segundos en total.

Sea D el máximo de los tiempos d de todos los N artículos, diseñar un algoritmo que en O(D ∗ N + NlogN) le índique al sabueso cuanto el máximo valor total qué puede salvar, qué artículos debe salvar para conseguirlo y en qué orden salvarlos.
*/

vector<fire> merge(vector<fire> &primera,vector<fire> &segunda){
  vector<fire> res;
  // Reservamos memoria para evitar realojamientos costosos (buena práctica)
  res.reserve(primera.size() + segunda.size());

  int i = 0;
  int j = 0;

  while (i < primera.size() && j < segunda.size()) {
    if (primera[i].d <= segunda[j].d) {
      res.push_back(primera[i]);
      i++;
    } else {
      res.push_back(segunda[j]);
      j++;
    }
  }

  // Si sobraron elementos en la primera mitad, los agregamos
  while (i < primera.size()) {
    res.push_back(primera[i]);
    i++;
  }
  
  // Si sobraron elementos en la segunda mitad, los agregamos
  while (j < segunda.size()) {
    res.push_back(segunda[j]);
    j++;
  }

  return res;
}

//Mi pista es que tengo un NLogN extra entonces seguro tengo que ordenarlos
void mergeSortTiempoVida(vector<fire> &array){
  if(array.size() < 2){
    return;
  };

  int medio = array.size()/2;

  vector<fire> primera_mitad(array.begin(), array.begin() + medio);
  vector<fire> segunda_mitad(array.begin() + medio, array.end());

  mergeSortTiempoVida(primera_mitad);
  mergeSortTiempoVida(segunda_mitad);

  array = merge(primera_mitad,segunda_mitad);
}

/*
Funcion recurisva: f(i,t) devuelve el valor maximo que se puede salvar considerando los primeros i articulos y teniendo t segundos usados.
f(i,t) = | i == n -> 0
         | i < n & sePuedeSalvar(i,t) -> max(f(i+1,t), f(i+1,t+ti) + pi)
         | i < n & !sePuedeSalvar(i,t) -> f(i+1,t)

Se debe partir de que el array esta ordenado por tiempo de vida d ascendete.
*/
bool sePuedeSalvar(int i, int t){
  return (t + articulos[i].t) < articulos[i].d;
}

int solve(int i, int t)
{
  if(i == articulos.size()){
    return 0;
  }

  int res = solve(i+1,t);
  if(sePuedeSalvar(i,t)){
    res = max(res, solve(i+1, t + articulos[i].t) + articulos[i].p);
  }

  return res;
}

void runExample(const string &name, const vector<fire> &items, int expected)
{
  articulos = items;
  mergeSortTiempoVida(articulos);

  cout << name << "\n";
  cout << "  Items ordenados por deadline (d):\n";
  for (int i = 0; i < articulos.size(); i++) {
    cout << "    [" << i + 1 << "] t=" << articulos[i].t << ", d=" << articulos[i].d << ", p=" << articulos[i].p << "\n";
  }

  int result = solve(0, 0);
  cout << "  Resultado: " << result << " (esperado " << expected << ")\n\n";
}

int main(int argc, char const *argv[])
{
  runExample("Ejemplo 1", {
    {3, 7, 4},
    {7, 10, 6},
    {2, 6, 5}
  }, 11);

  runExample("Ejemplo 2", {
    {3, 6, 4},
    {2, 8, 3},
    {4, 9, 7},
    {2, 5, 2}
  }, 12);

  runExample("Ejemplo 3", {
    {5, 5, 10},
    {4, 7, 12},
    {3, 6, 8}
  }, 12);

  return 0;
}
