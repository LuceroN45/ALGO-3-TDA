#include <iostream>
#include <vector>

using namespace std;

int SumatoriaParcial(vector<vector<int>> &D, vector<int> &SolParcial)
{
  int suma = 0;

  
  for (int i = 0; i < SolParcial.size() - 1; i++)
  {
    suma += D[SolParcial[i]][SolParcial[i + 1]];
  }

  return suma;
}

int DistanciaRecorrdia(vector<vector<int>> &D, vector<int> &SolParcial)
{
  int res = D[SolParcial[D.size() - 1]][SolParcial[0]] + SumatoriaParcial(D, SolParcial);


  return res;
}

int RutaMinima(vector<vector<int>> &D, vector<int> &ValoresRestantes, vector<int> &SolParcial, int &SumaParcial, int &SumaMinima)
{
  if (SumaMinima != -1 && SumaMinima <= SumaParcial)
  {
    return SumaMinima;
  }
  
  if (SolParcial.size() == D.size())
  {
    return DistanciaRecorrdia(D, SolParcial);//(O(n)) lo que me cuesta calcular la suma
  }

  for (int i = 0; i < ValoresRestantes.size(); i++) //tamano N //O(n)
  {
    int valor = ValoresRestantes[i];
    SolParcial.push_back(valor);
    ValoresRestantes.erase(ValoresRestantes.begin() + i);

    int sumatoriaParcial = SumatoriaParcial(D,SolParcial); //tamano k<n me cuesta O(k)
    int res = RutaMinima(D, ValoresRestantes, SolParcial,sumatoriaParcial,SumaMinima); //ValoresRestantes Tamano (n-1) (O(n-1), recursivamente llega a O(n-(n-1)=1)) son n! llamados
    if (SumaMinima == -1 || res < SumaMinima)
    {
      SumaMinima = res;
    }

    ValoresRestantes.insert(ValoresRestantes.begin() + i, valor);
    SolParcial.pop_back();
  }

  return SumaMinima; //Costo total de los llamados recursivos O(n + k + n!.n) = O(n!n = n**2.(n-1)!)
}

int main(int argc, char const *argv[])
{
  vector<vector<int>> D = {
      {0, 1, 10, 10},
      {10, 0, 3, 15},
      {21, 17, 0, 2},
      {3, 22, 30, 0}};

  vector<int> ValoresRestantes = {0, 1, 2, 3};
  vector<int> SolParcial = {};

  int minimo = -1;
  int comienzo = 0;
  int res = RutaMinima(D,ValoresRestantes,SolParcial,comienzo,minimo);

  cout << res << endl;
}
