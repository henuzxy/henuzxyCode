#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll Mod = 1e9+7;
const int MAX = 1e6+10;
ll inv[MAX];
void Init_inv(int N){
    inv[1] = 1;
    for(int i=2;i<=N;++i){
        inv[i] = (Mod-Mod/i)*inv[Mod%i]%Mod;
    }
}
