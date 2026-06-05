#include <bits/stdc++.h>
using namespace std;
#define forsn(i,s,n) for(int i = int(s);i<int(n);i++)
#define dforsn(i,s,n) for(int i = int(n)-1;i>=int(s);i--)
#define fore(i,s,n) forsn(i,s,n)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) dforsn(i,0,n)

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

#define DBG(x) cout<<#x<<" = "<<(x)<<endl;
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) int((x).size())

template<class x> ostream & operator<<(ostream & out, vector<x> v){
    out<<"[ ";
    for(auto y : v) out<<y<<" ";
    out<<"]";
    return out;
}

const int maxl = 1000;
const int maxn = 1e5+10;
typedef long long ll;

int main(){
    cin.tie(0); cin.sync_with_stdio(0);
    int n; ll g;
    cin>>n>>g;
    vector<ll> t(n+1), m[2];
    forn(i,n){ cin>>t[i+1]; t[i+1] += t[i];}
    forn(i,2) m[i].resize(n+1,0);
    forsn(l,1,maxl){
        swap(m[0],m[1]);
        forsn(i,1,n+1){
            m[0][i] = max(m[0][i-1],m[1][i]);
            if(i>=l) m[0][i] = max(m[0][i], m[1][i-l] - t[i] + t[i-l] + g);
        }
    }
    cout<<m[0][n]<<"\n";
}