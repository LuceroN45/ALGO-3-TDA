#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Totales por paridad
    int tot_even = n / 2, tot_odd = n - tot_even;
    int fixed_even = 0, fixed_odd = 0;

    vector<int> isZero(n, 0);
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) isZero[i] = 1;
        else if ((a[i] & 1) == 0) ++fixed_even;
        else ++fixed_odd;
    }
    int avail_even = tot_even - fixed_even; // pares disponibles para rellenar ceros
    int avail_odd  = tot_odd  - fixed_odd;  // impares disponibles para rellenar ceros

    // Prefijo de ceros: cuántos ceros hay en [0, i)
    vector<int> prefZero(n + 1, 0);
    for (int i = 0; i < n; ++i) prefZero[i + 1] = prefZero[i] + isZero[i];

    // dp[i][e][p]: mínimo costo desde i, habiendo usado e pares, última paridad p (0/1)
    // Dimensiones: (n+1) x (avail_even+1) x 2
    vector<vector<array<int,2>>> dp(n + 1, vector<array<int,2>>(avail_even + 1, {INF, INF}));

    // Caso base: en i == n, costo 0 para cualquier e y p
    for (int e = 0; e <= avail_even; ++e) dp[n][e] = {0, 0};

    // Transición: de i = n-1 hacia 0
    for (int i = n - 1; i >= 0; --i) {
        for (int e = 0; e <= avail_even; ++e) {
            for (int last_par = 0; last_par <= 1; ++last_par) {
                int best = INF;
                bool first = (i == 0); // no penaliza cambio en el primero

                auto updateBest = [&](int next_par, int next_e) {
                    int add = (first ? 0 : (next_par != last_par));
                    best = min(best, add + dp[i + 1][next_e][next_par]);
                };

                if (a[i] != 0) {
                    int par = (a[i] & 1);
                    updateBest(par, e);
                } else {
                    // Elegimos par o impar si quedan disponibles
                    int zeros_used = prefZero[i];
                    int odds_used  = zeros_used - e;

                    // Colocar par
                    if (e + 1 <= avail_even)
                        updateBest(0, e + 1);

                    // Colocar impar
                    if (odds_used + 1 <= avail_odd)
                        updateBest(1, e);
                }

                dp[i][e][last_par] = best;
            }
        }
    }

    // Resultado: arrancamos en i=0, e=0; el primero no penaliza, tomamos el mejor last_par
    int ans = min(dp[0][0][0], dp[0][0][1]);
    cout << ans << "\n";
    return 0;
}
