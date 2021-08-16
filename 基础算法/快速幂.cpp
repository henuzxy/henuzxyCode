typedef long long ll;
const ll Mod = 1e9+7;

ll quick_pow(ll x,ll y){
    ll res = 1;
    x = x%Mod;
    while(y > 0){
        if(y&1){
            res = res*x%Mod;
        }
        x = x*x%Mod;
        y >>= 1;
    }
    return res;
}

