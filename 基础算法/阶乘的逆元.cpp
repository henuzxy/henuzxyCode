#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll Mod = 998244353;
const int MAX = 1e6+10;
ll fac_inv[MAX],fac[MAX];
ll quick_pow(ll X,ll Y){
    ll res = 1;
    while(Y > 0){
        if(Y&1) res = res*X%Mod;
        X = X%Mod*X%Mod;
        Y >>= 1;
    }
    return res;
}
void Init_inv(int N){
    fac[0] = fac[1] = 1;
    for(int i=2;i<=N;++i){
        fac[i] = fac[i-1]*i%Mod;
    }   
    fac_inv[N] = quick_pow(fac[N],Mod-2);
    for(int i=N-1;i>=0;--i) fac_inv[i] = fac_inv[i+1]*(i+1)%Mod;
}


//更加容易写出的方法
void Init_inv(int N){
    fac[0] = fac_inv[0] = 1;
    for(int i=1;i<=N;++i){
        fac[i] = fac[i-1]*i%Mod;
        fac_inv[i] = quick_pow(fac[i],Mod-2);
    }
}