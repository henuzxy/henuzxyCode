#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll Mod = 998244353;
const int MAX = 1e6+10;
ll fac_inv[MAX],fac[MAX];
ll Quick_pow(ll x,ll N){
    ll res = 1;
    while(N > 0){
        if(N&1) res = res*x%Mod;
        x = x%Mod*x%Mod;
        N >>= 1;
    }
    return res;
}
void Init_inv(){
    int N = 1e6+3;
    fac[0] = fac[1] = 1;
    for(int i=2;i<=N;++i)   fac[i] = fac[i-1]*i%Mod;
    fac_inv[N] = Quick_pow(fac[N],Mod-2);
    for(int i=N-1;i>=0;--i) fac_inv[i] = fac_inv[i+1]*(i+1)%Mod;
}