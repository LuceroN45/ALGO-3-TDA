/* UVA 11790 - Murcia's Skyline
   url vjudge: https://vjudge.net/problem/UVA-11790
   Entrega 2 de Técnicas de Diseño de Algoritmos - 1C2024
   ~Pablo Terlisky
*/
#include<iostream>
#include<vector>
#include<limits>

using namespace std;

//LIS, por "Longest Increasing Subsequence"
//En realidad suele medir la longitud de la secuencia, 
// aquí se adapta para que dé el ancho total de los edificios
//Semántica: La subsecuencia de edificios más ancha que termina en el
// edificio en la posición pos.
int LIS(int pos, const vector<int>& alturas, const vector<int>& anchos, vector<int>& memo) {
    if (memo[pos]==-1) {
        int ancho_maximo_anterior = 0;
        for (int j=0;j<pos;j++) {
            if (alturas[j]<alturas[pos]) {
                ancho_maximo_anterior = max(ancho_maximo_anterior,LIS(j,alturas,anchos,memo));
            }
        }
        int ancho_total_maximo = anchos[pos]+ancho_maximo_anterior;
        memo[pos] = ancho_total_maximo;
    }
    return memo[pos];
}

int main() {
    int t;cin>>t;
    for(int caso=1;caso<=t;caso++) {
        int edificios;cin>>edificios;
        vector<int> altos = vector<int>(edificios+1,0);
        for (int e=0;e<edificios;e++) cin>>altos[e];
        //Edificio adicional ficticio para que siempre
        // la solución sea invocar LIS desde él
        // --No es necesario, se puede poblar la estructura
        //   de memoización y después tomar el máximo, pero
        //   funciona.
        altos[edificios]=numeric_limits<int>::max();
        vector<int> anchos = vector<int>(edificios+1,0);
        for (int e=0;e<edificios;e++) cin>>anchos[e];
        anchos[edificios]=0;
        //Estructura de memoización
        vector<int> memo = vector<int>(edificios+1,-1);
        int ancho_inc = LIS(edificios, altos, anchos, memo);
        //Invierto el signo para usar la misma función y calcular
        // la subsecuencia decreciente
        for (int e=0;e<edificios;e++) altos[e]=-altos[e];
        //Reseteo la estructura de memoización
        memo = vector<int>(edificios+1,-1);
        int ancho_dec = LIS(edificios, altos, anchos, memo);
        cout << "Case " << caso << ". "; 
        if (ancho_inc>=ancho_dec) {
            cout << "Increasing (" << ancho_inc << "). Decreasing (" << ancho_dec << ").";
        } else {
            cout << "Decreasing (" << ancho_dec << "). Increasing (" << ancho_inc << ").";
        } 
        cout << endl;
    }
    return 0;
}
