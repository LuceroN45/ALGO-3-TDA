#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int n;
vector<int> a, isZero, prefZero;
int avail_even, avail_odd;

// memo[i][e_used][last_par]  where last_par = 0 (par), 1 (impar)
vector<vector<array<int,2>>> memo;

int gar(int i, int e_used, int last_par) {
    if (i == n) return 0;

    int &res = memo[i][e_used][last_par];
    if (res != -1) return res;
    res = INF;

    // ¿es el primero?
    bool first = (i == 0);

    auto relax = [&](int next_e_used, int cur_par) {
        int add = (first ? 0 : (cur_par != last_par));
        res = min(res, add + gar(i + 1, next_e_used, cur_par));
    };

    if (a[i] != 0) {
        int par = (a[i] & 1);             // paridad fija
        relax(e_used, par);
    } else {
        // a[i] == 0 -> podemos elegir colocar un par o un impar, si quedan disponibles
        int zeros_used = prefZero[i];
        int odds_used  = zeros_used - e_used;

        // colocar par
        if (e_used + 1 <= avail_even) {
            relax(e_used + 1, 0);
        }
        // colocar impar
        if (odds_used + 1 <= avail_odd) {
            relax(e_used, 1);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    a.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // totales por paridad
    int tot_even = n / 2, tot_odd = n - tot_even;
    int fixed_even = 0, fixed_odd = 0;

    isZero.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) isZero[i] = 1;
        else if ((a[i] & 1) == 0) ++fixed_even;
        else ++fixed_odd;
    }
    avail_even = tot_even - fixed_even;
    avail_odd  = tot_odd  - fixed_odd;

    // prefijo de ceros
    prefZero.assign(n + 1, 0);
    for (int i = 0; i < n; ++i) prefZero[i + 1] = prefZero[i] + isZero[i];

    // memo: n x (avail_even+1) x 2
    memo.assign(n, vector<array<int,2>>(avail_even + 1, array<int,2>{-1, -1}));

    // last_par = 2 significa "no hay anterior", evita penalidad en el primero
    int ans = gar(0, 0, 0); // una sola llamada alcanza
    cout << ans << "\n";
    return 0;
}
